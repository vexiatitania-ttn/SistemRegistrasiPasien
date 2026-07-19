#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

struct Pasien {
    int noRekamMedis;
    string nama;
    int umur;
    string jenisKelamin;
    string keluhan;
    string tanggal;
    string jam;
};

const int MAX_PASIEN = 100;
Pasien dataPasien[MAX_PASIEN];
int jumlahPasien = 0;

string toLowerCase(string str) {
    string lowerStr = "";
    for (int i = 0; i < str.length(); i++) {
        lowerStr += tolower(str[i]);
    }
    return lowerStr;
}

bool isAllDigits(string str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool isValidName(string str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++) {
        if (!isalpha(str[i]) && str[i] != ' ') return false;
    }
    return true;
}

bool isValidDate(string str) {
    if (str.length() != 10) return false;
    if (str[4] != '-' || str[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool isValidTime(string str) {
    if (str.length() != 5) return false;
    if (str[2] != ':') return false;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool isRmExist(int rm) {
    for (int i = 0; i < jumlahPasien; i++) {
        if (dataPasien[i].noRekamMedis == rm) return true;
    }
    return false;
}


int inputRM() {
    string input;
    int rm;
    while (true) {
        cout << "Masukkan No. Rekam Medis (hanya angka): ";
        getline(cin, input);
        if (isAllDigits(input)) {
            rm = stoi(input);
            if (isRmExist(rm)) {
                cout << "-> Error: Nomor Rekam Medis sudah terdaftar!\n";
            } else {
                return rm;
            }
        } else {
            cout << "-> Error: Input tidak valid. Harus berupa angka.\n";
        }
    }
}

string inputNama() {
    string input;
    while (true) {
        cout << "Masukkan Nama Pasien (hanya huruf & spasi): ";
        getline(cin, input);
        if (isValidName(input)) return input;
        cout << "-> Error: Input tidak valid. Hanya boleh huruf dan spasi.\n";
    }
}

int inputUmur() {
    string input;
    while (true) {
        cout << "Masukkan Umur (hanya angka): ";
        getline(cin, input);
        if (isAllDigits(input)) return stoi(input);
        cout << "-> Error: Input tidak valid. Harus berupa angka.\n";
    }
}

string inputTanggal() {
    string input;
    while (true) {
        cout << "Masukkan Tanggal Registrasi (YYYY-MM-DD): ";
        getline(cin, input);
        if (isValidDate(input)) return input;
        cout << "-> Error: Format tanggal salah. Gunakan YYYY-MM-DD.\n";
    }
}

string inputJam() {
    string input;
    while (true) {
        cout << "Masukkan Jam Registrasi (HH:MM): ";
        getline(cin, input);
        if (isValidTime(input)) return input;
        cout << "-> Error: Format jam salah. Gunakan HH:MM.\n";
    }
}

void registrasiPasien() {
    if (jumlahPasien >= MAX_PASIEN) {
        cout << "Kapasitas penyimpanan penuh! Tidak dapat menambah pasien baru.\n";
        return;
    }

    cout << "\n=== REGISTRASI PASIEN BARU ===\n";
    Pasien pBaru;

    pBaru.noRekamMedis = inputRM();
    pBaru.nama = inputNama();
    pBaru.umur = inputUmur();
    
    cout << "Masukkan Jenis Kelamin (L/P): ";
    getline(cin, pBaru.jenisKelamin);
    
    cout << "Masukkan Keluhan: ";
    getline(cin, pBaru.keluhan);
    
    pBaru.tanggal = inputTanggal();
    pBaru.jam = inputJam();

    dataPasien[jumlahPasien] = pBaru;
    jumlahPasien++;

    cout << "=> Data pasien berhasil diregistrasi!\n";
}

void tampilkanData() {
    if (jumlahPasien == 0) {
        cout << "\nBelum ada data pasien yang terdaftar.\n";
        return;
    }

    cout << "\n====================================================================================================================\n";
    cout << left 
         << setw(10) << "No RM" 
         << setw(25) << "Nama Pasien" 
         << setw(6)  << "Umur" 
         << setw(6)  << "J.K" 
         << setw(35) << "Keluhan" 
         << setw(15) << "Tanggal" 
         << setw(10) << "Jam" << endl;
    cout << "====================================================================================================================\n";

    for (int i = 0; i < jumlahPasien; i++) {
        cout << left 
             << setw(10) << dataPasien[i].noRekamMedis 
             << setw(25) << dataPasien[i].nama 
             << setw(6)  << dataPasien[i].umur 
             << setw(6)  << dataPasien[i].jenisKelamin 
             << setw(35) << dataPasien[i].keluhan 
             << setw(15) << dataPasien[i].tanggal 
             << setw(10) << dataPasien[i].jam << endl;
    }
    cout << "====================================================================================================================\n";
}

void swapData(Pasien &a, Pasien &b) {
    Pasien temp = a;
    a = b;
    b = temp;
}

void sortingData() {
    if (jumlahPasien < 2) {
        cout << "\nData terlalu sedikit untuk diurutkan.\n";
        return;
    }

    string menuSort;
    cout << "\n=== MENU SORTING ===\n";
    cout << "1. Registrasi Terlama ke Terbaru (Ascending)\n";
    cout << "2. Registrasi Terbaru ke Terlama (Descending)\n";
    cout << "Pilih metode sorting (1/2): ";
    getline(cin, menuSort);

    if (menuSort != "1" && menuSort != "2") {
        cout << "=> Pilihan tidak valid dibatalkan.\n";
        return;
    }

    for (int i = 0; i < jumlahPasien - 1; i++) {
        for (int j = 0; j < jumlahPasien - i - 1; j++) {

            string waktu1 = dataPasien[j].tanggal + " " + dataPasien[j].jam;
            string waktu2 = dataPasien[j + 1].tanggal + " " + dataPasien[j + 1].jam;

            if (menuSort == "1") {
                //  Terlama ke Terbaru
                if (waktu1 > waktu2) {
                    swapData(dataPasien[j], dataPasien[j + 1]);
                }
            } else if (menuSort == "2") {
                //  Terbaru ke Terlama
                if (waktu1 < waktu2) {
                    swapData(dataPasien[j], dataPasien[j + 1]);
                }
            }
        }
    }
    cout << "=> Data berhasil diurutkan!\n";
    tampilkanData();
}

void cetakSatuData(Pasien p) {
    cout << "\n--- Informasi Pasien ---" << endl;
    cout << "No Rekam Medis : " << p.noRekamMedis << endl;
    cout << "Nama Pasien    : " << p.nama << endl;
    cout << "Umur           : " << p.umur << endl;
    cout << "Jenis Kelamin  : " << p.jenisKelamin << endl;
    cout << "Keluhan        : " << p.keluhan << endl;
    cout << "Tanggal Reg.   : " << p.tanggal << endl;
    cout << "Jam Reg.       : " << p.jam << endl;
    cout << "------------------------\n";
}

void searchingData() {
    if (jumlahPasien == 0) {
        cout << "\nData kosong.\n";
        return;
    }

    string input;
    cout << "\nMasukkan Nomor Rekam Medis (Angka) ATAU Nama Pasien (Huruf): ";
    getline(cin, input);

    bool ditemukan = false;

    // Jika berisi angka
    if (isAllDigits(input)) {
        int rmCari = stoi(input);
        for (int i = 0; i < jumlahPasien; i++) {
            if (dataPasien[i].noRekamMedis == rmCari) {
                cetakSatuData(dataPasien[i]);
                ditemukan = true;
                break;
            }
        }
    } 

    // Jika berisi huruf
    else {
        string namaCari = toLowerCase(input);
        for (int i = 0; i < jumlahPasien; i++) {
            string namaPasienLower = toLowerCase(dataPasien[i].nama);
            
            if (namaPasienLower.find(namaCari) != string::npos) {
                cetakSatuData(dataPasien[i]);
                ditemukan = true;
            }
        }
    }

    if (!ditemukan) {
        cout << "\n=> Data tidak ditemukan.\n";
    }
}

void editDataPasien() {
    if (jumlahPasien == 0) {
        cout << "\nData kosong.\n";
        return;
    }

    string input;
    cout << "\nMasukkan Nomor Rekam Medis pasien yang akan diedit: ";
    getline(cin, input);

    if (!isAllDigits(input)) {
        cout << "=> Error: Nomor Rekam Medis harus berupa angka.\n";
        return;
    }

    int rmEdit = stoi(input);
    int indexEdit = -1;

    for (int i = 0; i < jumlahPasien; i++) {
        if (dataPasien[i].noRekamMedis == rmEdit) {
            indexEdit = i;
            break;
        }
    }

    if (indexEdit != -1) {
        cout << "\n[ Data Lama Ditemukan ]";
        cetakSatuData(dataPasien[indexEdit]);
        
        cout << "\n-- Masukkan Data Baru --\n";
        dataPasien[indexEdit].nama = inputNama();
        dataPasien[indexEdit].umur = inputUmur();
        
        cout << "Masukkan Jenis Kelamin (L/P): ";
        getline(cin, dataPasien[indexEdit].jenisKelamin);
        
        cout << "Masukkan Keluhan: ";
        getline(cin, dataPasien[indexEdit].keluhan);
        
        dataPasien[indexEdit].tanggal = inputTanggal();
        dataPasien[indexEdit].jam = inputJam();

        cout << "=> Data pasien berhasil diperbarui!\n";
    } else {
        cout << "=> Data dengan Nomor Rekam Medis tersebut tidak ditemukan.\n";
    }
}

void hapusDataPasien() {
    if (jumlahPasien == 0) {
        cout << "\nData kosong.\n";
        return;
    }

    string input;
    cout << "\nMasukkan Nomor Rekam Medis pasien yang akan dihapus: ";
    getline(cin, input);

    if (!isAllDigits(input)) {
        cout << "=> Error: Nomor Rekam Medis harus berupa angka.\n";
        return;
    }

    int rmHapus = stoi(input);
    int indexHapus = -1;

    for (int i = 0; i < jumlahPasien; i++) {
        if (dataPasien[i].noRekamMedis == rmHapus) {
            indexHapus = i;
            break;
        }
    }

    if (indexHapus != -1) {
        for (int i = indexHapus; i < jumlahPasien - 1; i++) {
            dataPasien[i] = dataPasien[i + 1];
        }
        jumlahPasien--;
        cout << "=> Data pasien berhasil dihapus!\n";
    } else {
        cout << "=> Data dengan Nomor Rekam Medis tersebut tidak ditemukan.\n";
    }
}

int main() {
    string pilihan;

    do {
        cout << "\n===================================";
        cout << "\n    SISTEM REGISTRASI PASIEN";
        cout << "\n===================================\n";
        cout << "1. Registrasi Pasien\n";
        cout << "2. Tampilkan Seluruh Data\n";
        cout << "3. Sorting Data\n";
        cout << "4. Searching Data\n";
        cout << "5. Edit Data Pasien\n";
        cout << "6. Hapus Data Pasien\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu (1-7): ";
        getline(cin, pilihan);

        if (pilihan.length() == 1) {
            switch (pilihan[0]) {
                case '1':
                    registrasiPasien();
                    break;
                case '2':
                    tampilkanData();
                    break;
                case '3':
                    sortingData();
                    break;
                case '4':
                    searchingData();
                    break;
                case '5':
                    editDataPasien();
                    break;
                case '6':
                    hapusDataPasien();
                    break;
                case '7':
                    cout << "\nTerima kasih!\n";
                    break;
                default:
                    cout << "=> Pilihan tidak tersedia. Silakan coba lagi.\n";
            }
        } else {
            cout << "=> Input tidak valid. Masukkan angka 1 hingga 7.\n";
        }
    } while (pilihan != "7");

    return 0;
}