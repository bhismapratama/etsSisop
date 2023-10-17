1. Dengan implementasi ini, server dapat menerima panggilan dari siapa pun - hal ini karena program (tidak termasuk tugas selanjutnya yang belum saya implementasikan) adalah simulasi untuk tujuan demonstrasi, dan oleh karena itu pembatasan tidak diperlukan. Meskipun server menerima dari siapa saja, server ideal seharusnya membatasi akses untuk keamanan.

2. Jika autentikasi akan diimplementasikan, itu sebaiknya dilakukan di dalam kerangka kerja RPC, karena lebih mudah diimplementasikan dan konsisten (yaitu di satu tempat daripada beberapa, yang bahkan mungkin tidak perlu terduplikasi).

3. Saya menggunakan TCP, karena lebih mudah diimplementasikan, dan akan mencegah kehilangan atau paket yang rusak. Kompromi dibandingkan dengan UDP adalah bahwa TCP lebih lambat, namun penyebab mengapa itu lambat adalah alasan mengapa itu diutamakan dari awal (pengiriman terurut dan pengiriman ulang).

4. Soket server sebaiknya dibuat saat server dimulai, dan soket klien sebaiknya dibuat saat klien akan melakukan permintaan.

5. Secara dinamis. Tidak tahu pasti berapa banyak klien atau server yang akan ada, jadi alokasi memori dinamis memungkinkan program hanya menggunakan memori yang diperlukan (daripada melebihi dengan mengalokasikan sejumlah besar memori). Implikasi utamanya adalah dengan alokasi memori dinamis, harus berhati-hati terhadap kebocoran memori.

6. Karena tidak kompatibel. Untuk memungkinkan urutan byte yang berbeda antara host, konversi ke urutan byte jaringan sebagai media data umum, kemudian mengonversi kembali.


Protokol:

Protokol lapisan aplikasi:
- Klien terhubung ke server dengan alamat IP dan nomor port.
- Klien mencoba mencari fungsi, dan jika ada, mengambil lokasi fungsi.
- Klien menggunakan hanlde untuk memanggil fungsi.
- Server mengeksekusi fungsi, mengembalikan Hasil.
- Klien mencetak hasil.
- Klien kemudian melakukan panggilan ganda atau keluar.

Paket terstruktur dengan:
- Jenis permintaan (CARI atau PANGGIL)
- Nama fungsi, jika CARI
- Lokasi handle dan fungsi, jika PANGGIL

Blok data kami berukuran tetap, untuk kemudahan.

Server mengembalikan -1 untuk fungsi yang tidak ada, dan ketika panjang data terlalu besar.

Ketika pesan melebihi ukuran paket IP maksimum, TCP/IP akan memecah dan mereload kembali.