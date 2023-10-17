#include "rpc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

// Mendeklarasikan prototipe fungsi
rpc_data *add2_i8(rpc_data *);

int main(int argc, char *argv[]) {

    // Memastikan argumen command line terparses dengan benar
    char *port;
    int command;

    // getopt diperlukan untuk mendapatkan opsi "&"
    while ((command = getopt(argc, argv, "p:")) != -1) {
        switch (command) {
            case 'p':
                port = optarg;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (port == NULL) exit(EXIT_FAILURE);

    rpc_server *state;

    state = rpc_init_server(3000);
    if (state == NULL) {
        fprintf(stderr, "Gagal menginisialisasi\n");
        exit(EXIT_FAILURE);
    }

    if (rpc_register(state, "add2", add2_i8) == -1) {
        fprintf(stderr, "Gagal mendaftarkan add2\n");
        exit(EXIT_FAILURE);
    }

    rpc_serve_all(state);

    return 0;
}

/* Menambahkan dua bilangan bertipe int8_t */
/* Menggunakan data1 sebagai operand kiri, data2 sebagai operand kanan */
rpc_data *add2_i8(rpc_data *in) {

    /* Memeriksa data2 */
    if (in->data2 == NULL || in->data2_len != 1) {
        return NULL;
    }

    /* Menganalisis permintaan */
    char n1 = in->data1;
    char n2 = ((char *)in->data2)[0];

    /* Melakukan perhitungan */
    printf("add2: argumen %d dan %d\n", n1, n2);
    int res = n1 + n2;

    /* Menyiapkan respons */
    rpc_data *out = malloc(sizeof(rpc_data));
    assert(out != NULL);
    out->data1 = res;
    out->data2_len = 0;
    out->data2 = NULL;
    return out;
}
