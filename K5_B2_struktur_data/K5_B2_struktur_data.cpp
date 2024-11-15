#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>  // Untuk fungsi sqrt

using namespace std;

// Struct untuk menyimpan informasi tiket
struct Tiket {
    int id;
    string nama;
    string kategori;
    int harga;
    int stok;
};

// Struct untuk menyimpan informasi pemesan tiket
struct Pemesan {
    int id;
    string namaPemesan;
    int tiketId;
    int jumlahTiket;
    int totalHarga;
};

// Konstanta dan variabel untuk Stack dan Queue
const int MAX_USERS = 100;
const int MAX_SIZE = 100;
Tiket tiketStack[MAX_SIZE];
Pemesan queuePemesan[MAX_SIZE];
int top = -1;
int front = -1, rear = -1;
int tiketCounter = 0;
int pemesanCounter = 0;

// Data akun admin dan user
string adminUsername = "admin";
string adminPassword = "admin123";

// Array untuk menyimpan data user
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int totalUsers = 0;

// Fungsi untuk menginisialisasi data tiket awal
void inisialisasiTiket() {
    // Tiket Reguler
    tiketCounter++;
    Tiket tiketReguler;
    tiketReguler.id = tiketCounter;
    tiketReguler.nama = "Konser Musik";
    tiketReguler.kategori = "Reguler";
    tiketReguler.harga = 100000;
    tiketReguler.stok = 75;

    top++;
    tiketStack[top] = tiketReguler;

    // Tiket VIP
    tiketCounter++;
    Tiket tiketVIP;
    tiketVIP.id = tiketCounter;
    tiketVIP.nama = "Konser Musik";
    tiketVIP.kategori = "VIP";
    tiketVIP.harga = 250000;
    tiketVIP.stok = 25;

    top++;
    tiketStack[top] = tiketVIP;
}

// Deklarasi fungsi
void registrasi();
string login();
void menuAdmin();
void menuUser();
void tampilkanMenu();
void tambahTiket();
void hapusTiket();
void tampilkanTiket();
void updateTiket();
void menuSorting();
void mergeSort(Tiket arr[], int l, int r);
void merge(Tiket arr[], int l, int m, int r);
void quickSort(Tiket arr[], int low, int high);
int partition(Tiket arr[], int low, int high);
void tambahPemesan();
void hapusPemesan();
void tampilkanPemesan();
void lihatDetailPesanan();
int fibonacciSearch(Tiket arr[], int n, int x);
int jumpSearchByKategori(Tiket arr[], int n, string kategori);
void cariTiketById();
void cariTiketByNama();
void cariTiketByKategori();
void menuPencarian();
bool isFull(bool isStack);
bool isEmpty(bool isStack);

// Fungsi utama
int main() {
    inisialisasiTiket();
    int pilihan;

    while (true) {
        system("cls");
        cout << "+-----------------------------+" << endl;
        cout << "|   Pemesanan Tiket Konser    |" << endl;
        cout << "+-----------------------------+" << endl;
        cout << "| 1. Login                    |" << endl;
        cout << "| 2. Registrasi               |" << endl;
        cout << "| 3. Keluar                   |" << endl;
        cout << "+-----------------------------+" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string role = login();
            if (role == "admin") {
                cin.ignore();
                cin.ignore();
                menuAdmin();
            } else if (role == "user") {
                cin.ignore();
                cin.ignore();
                menuUser();
            }
        } else if (pilihan == 2) {
            registrasi();
            cin.ignore();
            cin.ignore();
        } else if (pilihan == 3) {
            cout << "Keluar dari program." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}

void menuAdmin() {
    int pilihan;
    while (true) {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|               Menu Admin                   |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Tambah Tiket                            |" << endl;
        cout << "| 2. Lihat Tiket                             |" << endl;
        cout << "| 3. Update Tiket                            |" << endl;
        cout << "| 4. Hapus Tiket                             |" << endl;
        cout << "| 5. Urutkan Tiket                           |" << endl;
        cout << "| 6. Hapus Pesan Tiket                       |" << endl;
        cout << "| 7. Lihat Semua Pemesan Tiket               |" << endl;
        cout << "| 8. Pencarian Tiket                         |" << endl;
        cout << "| 9. Logout                                  |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                tambahTiket();
                cin.ignore();
                cin.ignore();
                break;
            case 2:
                system("cls");
                tampilkanTiket();
                cin.ignore();
                cin.ignore();
                break;
            case 3:
                system("cls");
                tampilkanTiket();
                updateTiket();
                cin.ignore();
                cin.ignore();
                break;
            case 4:
                system("cls");
                tampilkanTiket();
                hapusTiket();
                cin.ignore();
                cin.ignore();
                break;
            case 5:
                system("cls");
                menuSorting();
                cin.ignore();
                cin.ignore();
                break;
            case 6:
                system("cls");
                hapusPemesan();
                cin.ignore();
                cin.ignore();
                break;
            case 7:
                system("cls");
                tampilkanPemesan();
                cin.ignore();
                cin.ignore();
                break;
            case 8:
                system("cls");
                menuPencarian();
                cin.ignore();
                cin.ignore();
                break;
            case 9:
                cout << "Logout berhasil." << endl;
                cin.ignore();
                cin.ignore();
                return;  
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    }
}

// Menu user
void menuUser() {
    int pilihan;
    string username;

    // Ambil username dari login yang berhasil
    for (int i = 0; i < totalUsers; i++) {
        if (usernames[i] != "") {
            username = usernames[i];
            break;
        }
    }

    while (true) {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|               Menu User                    |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| 1. Lihat Tiket                             |" << endl;
        cout << "| 2. Pesan Tiket                             |" << endl;
        cout << "| 3. Lihat Detail Pesanan                    |" << endl;
        cout << "| 4. Urutkan Tiket                           |" << endl;
        cout << "| 5. Pencarian Tiket                         |" << endl;
        cout << "| 6. Logout                                  |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                tampilkanTiket();
                cin.ignore();
                cin.ignore();
                break;
            case 2:
                system("cls");
                tambahPemesan();
                cin.ignore();
                cin.ignore();
                break;
            case 3:
                system("cls");
                lihatDetailPesanan();
                cin.ignore();
                cin.ignore();
                break;
            case 4:
                system("cls");
                menuSorting();
                cin.ignore();
                cin.ignore();
                break;
            case 5:
                system("cls");
                menuPencarian();
                cin.ignore();
                cin.ignore();
                break;
            case 6:
                cout << "Logout berhasil." << endl;
                cin.ignore();
                cin.ignore();
                return; 
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    }
}

// Fungsi untuk registrasi user
void registrasi() {
    string username, password;
    cout << "\n=== Registrasi User ===" << endl;
    cout << "Masukkan username baru: ";
    cin >> username;

    // Cek apakah username sudah ada
    for (int i = 0; i < totalUsers; i++) {
        if (usernames[i] == username) {
            cout << "Username sudah terdaftar. Coba username lain." << endl;
            return;
        }
    }

    cout << "Masukkan password baru: ";
    cin >> password;

    // Menyimpan username dan password ke array
    if (totalUsers < MAX_USERS) {
        usernames[totalUsers] = username;
        passwords[totalUsers] = password;
        totalUsers++;
        cout << "Registrasi berhasil! Silakan login dengan akun Anda." << endl;
    } else {
        cout << "Registrasi gagal. Batas maksimal user telah tercapai." << endl;
    }
}

// Fungsi untuk login
string login() {
    string username, password;
    cout << "\n=== Login ===" << endl;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    // Login sebagai admin
    if (username == adminUsername && password == adminPassword) {
        cout << "Login Berhasil, Selamat datang Admin" << endl;
        return "admin";
    }

    // Login sebagai user
    for (int i = 0; i < totalUsers; i++) {
        if (usernames[i] == username && passwords[i] == password) {
            cout << "Login Berhasil, Selamat datang " << usernames[i] << endl;
            return "user";
        }
    }

    cout << "Login gagal, username atau password salah." << endl;
    cin.ignore();
    cin.ignore();
    return "";
}


// fungsi tambahTiket untuk menambahkan stok
void tambahTiket() {
    if (isFull(true)) {
        cout << "Stack tiket penuh! Tidak bisa menambah tiket." << endl;
        return;
    }

    tiketCounter++;
    Tiket tiket;
    tiket.id = tiketCounter;

    // Memasukkan nama tiket
    cout << "Masukkan nama tiket: ";
    cin.ignore();  // Membersihkan buffer input
    getline(cin, tiket.nama);

    // Pilihan kategori tiket (1 untuk Reguler, 2 untuk VIP)
    int pilihanKategori;
    while (true) {
        cout << "Masukkan kategori tiket (Reguler/VIP): ";
        cin >> pilihanKategori;

        if (pilihanKategori == 1) {
            tiket.kategori = "Reguler";
            break;
        } else if (pilihanKategori == 2) {
            tiket.kategori = "VIP";
            break;
        } else {
            cout << "Pilihan tidak valid. Masukkan 1 untuk Reguler atau 2 untuk VIP.\n";
        }
    }

    // Memasukkan harga dan stok tiket
    cout << "Masukkan harga tiket: ";
    cin >> tiket.harga;
    cout << "Masukkan stok tiket: ";
    cin >> tiket.stok;

    // Menambahkan tiket ke stack
    top++;
    tiketStack[top] = tiket;
    cout << "Tiket berhasil ditambahkan!" << endl;
}

// fungsi tampilkanTiket untuk menampilkan stok
void tampilkanTiket() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang tersedia." << endl;
        return;
    }
    cout << "+===============================================================+" << endl;
    cout << "|                         Tiket Konser                          |" << endl;
    cout << "+===============================================================+" << endl;
    cout << "| ID | Nama          | Kategori | Harga      | Stok Tersedia    |" << endl;
    cout << "+---------------------------------------------------------------+" << endl;
    for (int i = top; i >= 0; i--) {
        cout << "| " << setw(2) << tiketStack[i].id << " | "
            << setw(13) << tiketStack[i].nama << " | "
            << setw(8) << tiketStack[i].kategori << " | Rp "
            << setw(7) << tiketStack[i].harga << " | "
            << setw(16) << tiketStack[i].stok << " |" << endl;
    }
    cout << "+---------------------------------------------------------------+" << endl;
}

// fungsi updateTiket untuk mengupdate stok
void updateTiket() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang bisa di-update." << endl;
        return;
    }
    int idUpdate;
    cout << "Masukkan ID tiket yang ingin di-update: ";
    cin >> idUpdate;
    bool found = false;

    for (int i = top; i >= 0; i--) {
        if (tiketStack[i].id == idUpdate) {
            found = true;
            cout << "Masukkan nama baru untuk tiket: ";
            cin.ignore();
            getline(cin, tiketStack[i].nama);
            cout << "Masukkan kategori baru (Reguler/VIP): ";
            getline(cin, tiketStack[i].kategori);
            cout << "Masukkan harga baru: ";
            cin >> tiketStack[i].harga;
            cout << "Masukkan stok baru: ";
            cin >> tiketStack[i].stok;
            cout << "Tiket berhasil di-update!" << endl;
            break;
        }
    }

    if (!found) cout << "Tiket dengan ID tersebut tidak ditemukan!" << endl;
}

// Fungsi hapusTiket yang diperbaiki
void hapusTiket() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang bisa dihapus." << endl;
        return;
    }

    int idHapus;
    cout << "Masukkan ID tiket yang ingin dihapus: ";
    cin >> idHapus;

    // Cari tiket yang akan dihapus
    int posisiHapus = -1;
    for (int i = 0; i <= top; i++) {
        if (tiketStack[i].id == idHapus) {
            posisiHapus = i;
            break;
        }
    }

    if (posisiHapus == -1) {
        cout << "Tiket dengan ID " << idHapus << " tidak ditemukan!" << endl;
        return;
    }

    // Periksa apakah tiket sedang dipesan
    bool tiketDipesan = false;
    for (int i = front; i <= rear && i != -1; i++) {
        if (queuePemesan[i].tiketId == idHapus) {
            tiketDipesan = true;
            break;
        }
    }

    if (tiketDipesan) {
        cout << "Tiket tidak dapat dihapus karena sedang dalam pesanan!" << endl;
        return;
    }

    // Geser semua tiket setelah posisi yang dihapus
    for (int i = posisiHapus; i < top; i++) {
        tiketStack[i] = tiketStack[i + 1];
    }
    top--;
    cout << "Tiket berhasil dihapus!" << endl;
}

// Fungsi untuk menu sorting
void menuSorting() {
    int pilihan;
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang tersedia untuk diurutkan." << endl;
        return;
    }

    cout << "+--------------------------------------------+" << endl;
    cout << "|            Pilih Metode Sorting            |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| 1. Urutkan Berdasarkan Stok (Merge Sort)   |" << endl;
    cout << "| 2. Urutkan Berdasarkan Harga (Quick Sort)  |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "Masukkan pilihan sorting Anda: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            mergeSort(tiketStack, 0, top);
            cout << "Data tiket telah diurutkan menggunakan Merge Sort." << endl;
            break;
        case 2:
            quickSort(tiketStack, 0, top);
            cout << "Data tiket telah diurutkan menggunakan Quick Sort." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

// fungsi tambahPemesan untuk memeriksa dan mengurangi stok
void tambahPemesan() {
    if (isFull(false)) {
        cout << "Queue pemesan penuh! Tidak bisa menambah pemesan." << endl;
        return;
    }

    pemesanCounter++;
    Pemesan pemesan;
    pemesan.id = pemesanCounter;
    
    // Gunakan username yang sudah login
    cout << "Masukkan nama pemesan: ";
    cin.ignore();
    getline(cin, pemesan.namaPemesan);

    // Tampilkan tiket yang tersedia
    tampilkanTiket();

    cout << "Masukkan ID tiket yang ingin dipesan: ";
    cin >> pemesan.tiketId;

    // Cari tiket dan periksa stok
    bool tiketDitemukan = false;
    for (int i = top; i >= 0; i--) {
        if (tiketStack[i].id == pemesan.tiketId) {
            tiketDitemukan = true;
            cout << "Masukkan jumlah tiket yang ingin dipesan: ";
            cin >> pemesan.jumlahTiket;

            if (pemesan.jumlahTiket <= tiketStack[i].stok) {
                tiketStack[i].stok -= pemesan.jumlahTiket;
                pemesan.totalHarga = tiketStack[i].harga * pemesan.jumlahTiket;
                system("cls");
                cout << "+------------------------------------+" << endl;
                cout << "|          DETAIL PESANAN            |" << endl;
                cout << "+------------------------------------+" << endl;
                cout << "| Nama Pemesan    | " << pemesan.namaPemesan << setw(14) << " |" << endl;
                cout << "| Tiket           | " << tiketStack[i].nama << " - " << tiketStack[i].kategori << "|" << endl;
                cout << "| Jumlah          | " << setw(17) << pemesan.jumlahTiket << " |" << endl;
                cout << "| Harga Tiket     | Rp " << setw(13) << tiketStack[i].harga << " |" << endl;
                cout << "| Total Harga     | Rp " << setw(13) << pemesan.totalHarga << " |" << endl;
                cout << "+------------------------------------+" << endl;
                cout << "|     Tiket berhasil dipesan!        |" << endl;
                cout << "+------------------------------------+" << endl;

                // Masukkan pemesan ke queue
                if (front == -1) front = 0;
                rear = (rear + 1) % MAX_SIZE;
                queuePemesan[rear] = pemesan;
            } else {
                cout << "Stok tiket tidak mencukupi!" << endl;
            }
            break;
        }
    }
    if (!tiketDitemukan) cout << "Tiket dengan ID tersebut tidak ditemukan!" << endl;
}

// fungsi untuk melihat detail pesanan user
void lihatDetailPesanan() {
    string username;
    cout << "Masukkan username Anda: ";
    cin >> username;

    if (isEmpty(false)) {
        cout << "Belum ada pesanan yang dibuat." << endl;
        return;
    }

    cout << "\n+------------------------------------------------------------------------------+" << endl;
    cout << "|                            Detail Pesanan Anda                               |" << endl;
    cout << "+------------------------------------------------------------------------------+" << endl;
    cout << "| ID | Nama Pemesan      | Nama Tiket     | Kategori | Jumlah | Total Harga    |" << endl;
    cout << "+------------------------------------------------------------------------------+" << endl;

    bool pesananDitemukan = false;
    int i = front;
    
    // Menggunakan do-while untuk memastikan semua elemen queue diperiksa
    do {
        if (queuePemesan[i].namaPemesan == username) {
            pesananDitemukan = true;
            
            // Cari detail tiket berdasarkan tiketId
            string namaTiket = "Tiket tidak ditemukan";
            string kategori = "";
            int hargaSatuan = 0;
            
            // Pencarian dari top stack untuk mendapatkan detail tiket terbaru
            for (int j = top; j >= 0; j--) {
                if (tiketStack[j].id == queuePemesan[i].tiketId) {
                    namaTiket = tiketStack[j].nama;
                    kategori = tiketStack[j].kategori;
                    hargaSatuan = tiketStack[j].harga;
                    break;
                }
            }

            // Hitung total harga
            int totalHarga = hargaSatuan * queuePemesan[i].jumlahTiket;

            // Format output dengan setw untuk alignment yang lebih baik
            cout << "| " << setw(2) << queuePemesan[i].id << " | "
                << left << setw(15) << queuePemesan[i].namaPemesan << " | "
                << left << setw(12) << namaTiket << " | "
                << left << setw(8) << kategori << " | "
                << right << setw(6) << queuePemesan[i].jumlahTiket << " | Rp "
                << right << setw(9) << totalHarga << " |" << endl;
        }
        
        i = (i + 1) % MAX_SIZE;  // Circular increment
    } while (i != (rear + 1) % MAX_SIZE);  // Lanjutkan sampai semua elemen diperiksa

    cout << "+------------------------------------------------------------------------------+" << endl;

    if (!pesananDitemukan) {
        cout << "|                         Anda belum memiliki pesanan                          |" << endl;
        cout << "+------------------------------------------------------------------------------+" << endl;
    }
}

// Fungsi Untuk menampilkan detail pesanan
void tampilkanPemesan() {
    if (isEmpty(false)) {
        cout << "Pemesan kosong! Tidak ada pemesanan tiket." << endl;
        return;
    }

    cout << "+---------------------------------------------------------------------------------------+" << endl;
    cout << "|                            Daftar Pemesan Tiket                                     |" << endl;
    cout << "+---------------------------------------------------------------------------------------+" << endl;
    cout << "| ID | Nama Pemesan        | ID Tiket | Jumlah | Total Harga     | Nama Tiket         |" << endl;
    cout << "+---------------------------------------------------------------------------------------+" << endl;

    for (int i = front; i <= rear; i++) {
        // Cari nama tiket berdasarkan tiketId
        string namaTiket = "Tiket tidak ditemukan";
        int hargaSatuan = 0;
        for (int j = 0; j <= top; j++) {
            if (tiketStack[j].id == queuePemesan[i].tiketId) {
                namaTiket = tiketStack[j].nama;
                hargaSatuan = tiketStack[j].harga;
                break;
            }
        }

        // Hitung total harga
        int totalHarga = hargaSatuan * queuePemesan[i].jumlahTiket;
        queuePemesan[i].totalHarga = totalHarga;

        // Menampilkan data pemesan dengan format yang lebih rapi
        cout << "| " << setw(2) << queuePemesan[i].id << " | "
            << setw(20) << queuePemesan[i].namaPemesan << " | "
            << setw(8) << queuePemesan[i].tiketId << " | "
            << setw(6) << queuePemesan[i].jumlahTiket << " | Rp "
            << setw(12) << queuePemesan[i].totalHarga << " | "
            << setw(18) << namaTiket << " |" << endl;
    }
    cout << "+---------------------------------------------------------------------------------------+" << endl;
}

// Fungsi untuk menghapus pemesan dari queue
void hapusPemesan() {
    if (isEmpty(false)) {
        cout << "Queue pemesan kosong! Tidak ada pemesan untuk dihapus." << endl;
        return;
    }

    cout << "Pemesan dengan nama " << queuePemesan[front].namaPemesan << " berhasil dihapus." << endl;
    front++;
    if (front > rear) front = rear = -1;  // Reset jika queue kosong
}

// Implementasi Merge Sort
void mergeSort(Tiket arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(Tiket arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Tiket> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].stok >= R[j].stok) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Implementasi Quick Sort
void quickSort(Tiket arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(Tiket arr[], int low, int high) {
    int pivot = arr[high].harga;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].harga > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Fungsi untuk fibonacci search berdasarkan ID tiket
int fibonacciSearch(Tiket arr[], int n, int x) {
    int fibMMm2 = 0;   // (m-2)'th Fibonacci Number
    int fibMMm1 = 1;   // (m-1)'th Fibonacci Number
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci Number

    // Mencari Fibonacci Number terkecil yang lebih besar atau sama dengan n
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i].id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i].id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else return i;
    }

    if (fibMMm1 && arr[offset + 1].id == x)
        return offset + 1;

    return -1;
}

// Fungsi untuk jump search berdasarkan ID tiket
int jumpSearchByKategori(Tiket arr[], int n, string kategori) {
    int step = sqrt(n); // Langkah melompat
    int prev = 0;

    // Mencari blok yang berpotensi mengandung elemen
    while (arr[min(step, n) - 1].kategori < kategori) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    // Melakukan linear search di dalam blok
    while (arr[prev].kategori < kategori) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    // Jika ditemukan
    if (arr[prev].kategori == kategori)
        return prev;

    return -1;
}

// Fungsi untuk mencari pattern dalam string menggunakan Boyer Moore
void generateBadChar(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

vector<int> boyerMoore(string text, string pattern) {
    vector<int> positions;
    int m = pattern.size();
    int n = text.size();

    int badchar[256];

    generateBadChar(pattern, m, badchar);

    int s = 0;  // s adalah shift dari pattern terhadap text
    while(s <= (n - m)) {
        int j = m - 1;

        while(j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            positions.push_back(s);
            s += (s + m < n)? m - badchar[text[s + m]] : 1;
        }
        else
            s += max(1, j - badchar[text[s + j]]);
    }
    
    return positions;
}

// Fungsi untuk mengubah string menjadi lowercase
string toLower(string str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// Fungsi untuk mencari tiket berdasarkan nama menggunakan Boyer Moore
void cariTiketByNama() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang bisa dicari." << endl;
        return;
    }

    string namaCari;
    cout << "Masukkan nama tiket yang ingin dicari: ";
    cin.ignore();
    getline(cin, namaCari);

    // Ubah input pencarian menjadi lowercase
    string namaCariLower = toLower(namaCari);

    vector<int> hasilPencarian;
    for (int i = 0; i <= top; i++) {
        // Ubah nama tiket menjadi lowercase untuk perbandingan
        string namaTiketLower = toLower(tiketStack[i].nama);
        vector<int> positions = boyerMoore(namaTiketLower, namaCariLower);
        if (!positions.empty()) {
            hasilPencarian.push_back(i);
        }
    }

    if (hasilPencarian.empty()) {
        cout << "Tidak ditemukan tiket dengan nama yang mengandung '" << namaCari << "'" << endl;
    } else {
        cout << "\n+---------------------------------------------------------------+" << endl;
        cout << "|                     Hasil Pencarian Tiket                      |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| ID | Nama          | Kategori      | Harga      | Stok        |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        
        for (int idx : hasilPencarian) {
            cout << "| " << setw(2) << tiketStack[idx].id << " | "
                << setw(13) << tiketStack[idx].nama << " | "
                << setw(12) << tiketStack[idx].kategori << " | Rp "
                << setw(7) << tiketStack[idx].harga << " | "
                << setw(10) << tiketStack[idx].stok << " |" << endl;
        }
        cout << "+---------------------------------------------------------------+" << endl;
    }
}

// Fungsi untuk mencari tiket berdasarkan ID
void cariTiketById() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang bisa dicari." << endl;
        return;
    }

    int idCari;
    cout << "Masukkan ID tiket yang ingin dicari: ";
    cin >> idCari;

    // Menggunakan Fibonacci Search
    int hasil = fibonacciSearch(tiketStack, top + 1, idCari);
    
    if (hasil == -1) {
        cout << "Tiket dengan ID " << idCari << " tidak ditemukan." << endl;
    } else {
        cout << "\n+---------------------------------------------------------------+" << endl;
        cout << "|                     Hasil Pencarian Tiket                      |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| ID | Nama          | Kategori      | Harga      | Stok        |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| " << setw(2) << tiketStack[hasil].id << " | "
            << setw(13) << tiketStack[hasil].nama << " | "
            << setw(12) << tiketStack[hasil].kategori << " | Rp "
            << setw(7) << tiketStack[hasil].harga << " | "
            << setw(10) << tiketStack[hasil].stok << " |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
    }
}

// Fungsi untuk mencari tiket berdasarkan Kategori
void cariTiketByKategori() {
    if (isEmpty(true)) {
        cout << "Stack tiket kosong! Tidak ada tiket yang bisa dicari." << endl;
        return;
    }

    string kategoriCari;
    cout << "Masukkan kategori tiket yang ingin dicari: ";
    cin.ignore(); 
    getline(cin, kategoriCari);

    // Menggunakan Jump Search
    int hasil = jumpSearchByKategori(tiketStack, top + 1, kategoriCari);
    
    if (hasil == -1) {
        cout << "Tiket dengan kategori \"" << kategoriCari << "\" tidak ditemukan." << endl;
    } else {
        cout << "\n+---------------------------------------------------------------+" << endl;
        cout << "|                     Hasil Pencarian Tiket                      |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| ID | Nama          | Kategori      | Harga      | Stok        |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
        cout << "| " << setw(2) << tiketStack[hasil].id << " | "
            << setw(13) << tiketStack[hasil].nama << " | "
            << setw(12) << tiketStack[hasil].kategori << " | Rp "
            << setw(7) << tiketStack[hasil].harga << " | "
            << setw(11) << tiketStack[hasil].stok << " |" << endl;
        cout << "+---------------------------------------------------------------+" << endl;
    }
}

// Fungsi menu pencarian
void menuPencarian() {
    int pilihan;
    cout << "+--------------------------------------------+" << endl;
    cout << "|            Menu Pencarian Tiket            |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| 1. Cari berdasarkan ID                     |" << endl;
    cout << "| 2. Cari berdasarkan Nama                   |" << endl;
    cout << "| 3. Cari berdasarkan Kategori               |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "Masukkan pilihan pencarian: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            system("cls");
            tampilkanTiket();
            cariTiketById();
            cin.ignore();
            cin.ignore();
            break;
        case 2:
            system("cls");
            tampilkanTiket();
            cariTiketByNama();
            cin.ignore();
            cin.ignore();
            break;
        case 3:
            system("cls");
            tampilkanTiket();
            cariTiketByKategori();
            cin.ignore();
            cin.ignore();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }
}

// Fungsi untuk mengecek apakah stack atau queue penuh
bool isFull(bool isStack) {
    if (isStack) return top == MAX_SIZE - 1;
    else return (rear + 1) % MAX_SIZE == front;
}

// Fungsi untuk mengecek apakah stack atau queue kosong
bool isEmpty(bool isStack) {
    if (isStack) return top == -1;
    else return front == -1;
}
