#include <ad.h>
#include <cmd_ln.h>
#include <pocketsphinx.h>
#include <thread>
#include "node.h"
#include "../node/socket-writer.h"
#include "../node/node-exception.h"

namespace cdna_node_micro {

    static void sleep_milli_seconds(int32 ms)
    {
        struct timeval tmo;

        tmo.tv_sec = 0;
        tmo.tv_usec = ms * 1000;

        select(0, NULL, NULL, NULL, &tmo);
    }

    Node::Node(Spec spec) : AbstractNode(spec) {

    }

    Node::~Node() {

    }

    void Node::run() {
        // declare variables
        const int BUFFER_SIZE = 2048;
        ad_rec_t *reader;
        size_t read_samples;
        int16 read_buffer[BUFFER_SIZE];
        cmd_ln_t *read_decoder_config;
        ps_decoder_t *read_decoder;

        // open audio record
        reader = ad_open_dev(NULL, 16000);
        if (reader == NULL) {
            throw NodeException("Failed to open read audio device");
        }

        // start audio record
        if (ad_start_rec(reader) < 0) {
            throw NodeException("Failed to start read audio device");
        }

        // instance audio decoder
        read_decoder_config = cmd_ln_init(
                NULL,
                ps_args(),
                TRUE,
                "-logfn", "/dev/null", // turn off console log
                "-hmm", "/usr/local/share/pocketsphinx/model/en-us/en-us",
                "-lm", "/usr/local/share/pocketsphinx/model/en-us/en-us.lm.dmp",
                "-dict", "/usr/local/share/pocketsphinx/model/en-us/cmudict-en-us.dict",
                NULL
        );
        read_decoder = ps_init(read_decoder_config);
        if (read_decoder == NULL) {
            throw NodeException("Failed to initialize audio decoder");
        }

        // start utterance
        if (ps_start_utt(read_decoder) < 0) {
            throw NodeException("Failed to start reader utterance");
        }
        bool utt_started = false;
        bool in_speech = false;
        char const *hypothesis;

        while (true) {
            try {
                // read from input device
                read_samples = ad_read(
                        reader,
                        read_buffer,
                        BUFFER_SIZE
                );
                if (read_samples < 0) {
                    throw NodeException("Failed to read audio");
                }

                // add data buffered from device to read decoder
                ps_process_raw(
                        read_decoder,
                        read_buffer,
                        read_samples,
                        false,
                        false
                );

                // check device in speech
                in_speech = ps_get_in_speech(read_decoder);
                if (in_speech && !utt_started) {
                    utt_started = true;
                }

                // check device in speech then add data to decoder
                if (!in_speech && utt_started) {
                    ps_end_utt(read_decoder);
                    hypothesis = ps_get_hyp(read_decoder, NULL);
                    if (hypothesis != NULL) {
                        cout<<"ENV: "<<hypothesis<<endl;
                        Command core_command = this->spec_.first("node-core");
                        int port = atoi(core_command.option("--port").c_str());
                        SocketWriter socket(core_command.option("--host"), port);
                        string response = socket.write_to(hypothesis);
                        cout << "IN: " << response << endl;
                    }
                    if (ps_start_utt(read_decoder) < 0) {
                        throw NodeException("Failed to start reader utterance");
                    }
                    utt_started = false;
                }
                sleep_milli_seconds(100);
            } catch (NodeException e) {
                cout<<"ERROR: "<<e.what()<<endl;
            }

        }
    }
}