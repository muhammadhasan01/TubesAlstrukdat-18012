/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"

#define QNil ' '
/* Konstanta untuk mendefinisikan Qaddress tak terdefinisi */

/* Definisi elemen dan Qaddress */
typedef char Qinfotype[10];
typedef int Qaddress;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { Qinfotype * T;   /* tabel penyimpan elemen */
                 Qaddress HEAD;  /* alamat penghapusan */
                 Qaddress TAIL;  /* alamat penambahan */
                 int MaxQEl;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=QNil; TAIL=QNil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxQEl(Q) (Q).MaxQEl

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxQEl */
int NBQElmt (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateQueue (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxQEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void QDeAlokasi(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxQEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void QAdd (Queue * Q, Qinfotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void QDel (Queue * Q, Qinfotype * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = QNilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

void PrintInfoHead (Queue Q);
/* I.S. Q mungkin kosong */
/* F.S. Jika Q kosong, menuliskan none ke layar, jika Q tidak kosong menuliskan elemen head ke layar */

#endif
