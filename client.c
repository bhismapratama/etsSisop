#include "rpc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Mem-parsing argumen baris perintah dengan benar
    char *ip;
    char *port;
    int command;
    
    while ((command = getopt(argc, argv, "i:p:")) != -1) {
        switch (command) {
            case 'i':
                ip = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (ip == NULL || port == NULL) exit(EXIT_FAILURE);

    int exit_code = 0;

    rpc_client *state = rpc_init_client("::1", 3000);
    if (state == NULL) {
        exit(EXIT_FAILURE);
    }

    rpc_handle *handle_add2 = rpc_find(state, "add2");
    if (handle_add2 == NULL) {
        fprintf(stderr, "ERROR: Fungsi add2 tidak ada\n");
        exit_code = 1;
        goto cleanup;
    }

    for (int i = 0; i < 2; i++) {
        /* Menyiapkan permintaan */
        char left_operand = i;
        char right_operand = 100;
        rpc_data request_data = {
            .data1 = left_operand, .data2_len = 1, .data2 = &right_operand};

        /* Memanggil dan menerima respons */
        rpc_data *response_data = rpc_call(state, handle_add2, &request_data);
        if (response_data == NULL) {
            fprintf(stderr, "Panggilan fungsi add2 gagal\n");
            exit_code = 1;
            goto cleanup;
        }

        /* Menafsirkan respons */
        assert(response_data->data2_len == 0);
        assert(response_data->data2 == NULL);
        printf("Hasil perhitungan %d + %d: %d\n", left_operand, right_operand,
            response_data->data1);
        rpc_data_free(response_data);
    }

cleanup:
    if (handle_add2 != NULL) {
        free(handle_add2);
    }

    rpc_close_client(state);
    state = NULL;

    return exit_code;
}
