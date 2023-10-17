/* Header untuk sistem RPC */
/* Tolong jangan mengubah file ini */

#ifndef RPC_H
#define RPC_H

#include <stddef.h>

/* Status server */
typedef struct rpc_server rpc_server;
/* Status klien */
typedef struct rpc_client rpc_client;

/* Data pengiriman untuk permintaan/respon */
typedef struct {
    int data1;
    size_t data2_len;
    void *data2;
} rpc_data;

/* Penangan untuk fungsi jarak jauh, yang mengambil rpc_data* sebagai input dan menghasilkan
 * rpc_data* sebagai output */
typedef rpc_data *(*rpc_handler)(rpc_data *);

/* ---------------- */
/* Fungsi Server */
/* ---------------- */

/* Memulai status server */
/* MENGEMBALIKAN: rpc_server* jika berhasil, NULL jika gagal */
rpc_server *rpc_init_server(int port);

/* Mendaftarkan fungsi (pemetaan dari nama ke penangan) */
/* MENGEMBALIKAN: -1 jika gagal */
int rpc_register(rpc_server *srv, char *name, rpc_handler handler);

/* Memulai melayani permintaan */
void rpc_serve_all(rpc_server *srv);

/* ---------------- */
/* Fungsi Klien */
/* ---------------- */

/* Memulai status klien */
/* MENGEMBALIKAN: rpc_client* jika berhasil, NULL jika gagal */
rpc_client *rpc_init_client(char *addr, int port);

/* Menemukan fungsi jarak jauh berdasarkan nama */
/* MENGEMBALIKAN: rpc_handle* jika berhasil, NULL jika gagal */
/* rpc_handle* akan dibebaskan dengan satu panggilan ke free(3) */
rpc_handle *rpc_find(rpc_client *cl, char *name);

/* Memanggil fungsi jarak jauh menggunakan handle */
/* MENGEMBALIKAN: rpc_data* jika berhasil, NULL jika gagal */
rpc_data *rpc_call(rpc_client *cl, rpc_handle *h, rpc_data *payload);

/* Membersihkan status klien dan menutup klien */
void rpc_close_client(rpc_client *cl);

/* ---------------- */
/* Fungsi Bersama */
/* ---------------- */

/* Membebaskan struktur rpc_data */
void rpc_data_free(rpc_data *data);

#endif
