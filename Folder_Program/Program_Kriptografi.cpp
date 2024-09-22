#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Nama = Michael Setiyanto Silambi
// Nim = 1306620041
// Program Studi Fisika A

// Judul Projek = Kriptografi menggunakan algoritma Rail Fence dengan modifikasi  Circular Left shift & Circular Right shift dikombinasikan dengan Kriptografi DNA
// Tambahkan terkait opsi user untuk melakukan enkrip atau dekrip

// ============== Right Shift =============
int right_shift_circular(int num, int shift) {
    int numBits = 7; // 7 Bit
    shift = shift % numBits; 
    return (num >> shift) | (num << (numBits - shift))& 0x7F;
}

// ============== Left Shift =============
int left_shift_circular(int num, int shift) {
    int numBits = 7; 
    shift = shift % numBits; 
    return ((num << shift) | (num >> (numBits - shift))) & 0x7F;
}


// ============== Enkripsi  =============
string enkripsi(string teks, int kunci) {
    string output ="";
    int size = teks.length();
    char railfence[kunci][size];

    // => inisiasi dengan ascii nilai null
    for (int r = 0; r < kunci; ++r)
    {
        for (int c = 0; c < size; ++c)
        {
            railfence[r][c] =0;
        }
    }

    // => pola 2d array railfence
    for (int r=0, c=0, d=1; c<size; r+=d, ++c) {
        railfence[r][c] = teks[c];
        if (r == kunci-1) d = -1;
        else if (r==0) d=1;
    }

    // => menginput teks 2d array dari setiap baris
    for (int r=0; r<kunci; ++r)
    {
        for (int c=0; c<size;++c)
        {
            if (railfence[r][c]!=0)
            {
                output += railfence[r][c];
            }
        }
    }
    return output;
}

// ============= ENKRIPSI DNA ============
string bit_to_dna(char character) {          
   string output_dna = "";
   int i;     
   int s[8];
   int bit_code[8];               
   for(i=0;i<8;i++) {     
       s[i]=character%2;     
       character=character/2;  
       //cout << character << endl;
    }
   int a,b;     
   for(b=0,a=7;b<8;b++,a--) { 
        bit_code[b] = s[a];
   } 

   // menggabungkan setiap 2 bit dari kode biner untuk di inisiasi pada baris dna (A,C,G,T)
   int c;
   for (c=0;c<8;) {
        int binari0 = bit_code[c];
        int binari1 = bit_code[c+1];
        if (binari0 == 0 && binari1 == 0){
            output_dna += "A";
        }
        else if (binari0 == 0 && binari1 == 1){
            output_dna += "C";
        }
        else if (binari0 == 1 && binari1 == 0){
            output_dna += "G";
        }
        else if (binari0 == 1 && binari1 == 1){
            output_dna += "T";
        }
        //cout << binari0 << binari1 << endl;
        //cout << bit_code[c] << endl;
        //cout << bit_code[c+1] << endl;
        c = c+2;
    }
   return output_dna;
}

// =========== Dekripsi DNA =======================
string dna_to_bit(string input) {     
    string output_dna = "";

    // menggabungkan setiap 2 bit dari kode biner untuk di inisiasi pada baris dna (A,C,G,T)
    int bit_code[8];  // nilai bit disimpan sehingga yang diinput adalah satu persatu
    int d = 0;
    for (int c = 0; c < 4; c++) {
        char kode = input[c];
        if (kode == 'A'){
            bit_code[d] = 0;
            bit_code[d + 1] = 0;
        }
        else if (kode == 'C'){
            bit_code[d] = 0;
            bit_code[d + 1] = 1;
        }
        else if (kode == 'G'){
            bit_code[d] = 1;
            bit_code[d + 1] = 0;
        }
        else if (kode == 'T'){
            bit_code[d] = 1;
            bit_code[d + 1] = 1;
        }
        d = d + 2;
    }

    //for (int b = 0; b < 8; b++) {
    //    cout << bit_code[b];
    //}

    // nilai bit tersebut akan dihitung menjadi desimal
    //cout << " " << endl;
    double desimal;
    int b,e;
    for (b = 7,e=0; e < 8; b--,e++) {
        if (bit_code[e] == 1) {
            int pangkat = bit_code[e]*b;
            //cout << pangkat << endl;
            desimal +=  pow(2,pangkat);
        }
    }
    //cout << " " << endl;

   //cout << desimal << endl;
    string char_dec_dekrip;
    char karakter_dekrip = char(desimal);
    char_dec_dekrip = char_dec_dekrip + karakter_dekrip;

    return char_dec_dekrip;
}

// ============== Dekripsi  Rail Fence =============
string dekripsi(string teks, int kunci) {
    string output = "";
    int size = teks.length();
    char railfence[kunci][size];

    // ==> Inisialisasi dengan nilai null
    for (int r = 0; r < kunci; ++r) {
        for (int c = 0; c < size; ++c) {
            railfence[r][c] = 0;
        }
    }

    // --> Membuat pola railfence
    for (int r = 0, c = 0, d = 1; c < size; r += d, ++c) {
        railfence[r][c] = 1; 
        if (r == kunci - 1) d = -1;
        else if (r == 0) d = 1;
    }

    // ==> Posisi huruf sesuai di setiap baris
    int count = 0;
    for (int r = 0; r < kunci; ++r) {
        for (int c = 0; c < size; ++c) {
            if (railfence[r][c] == 1) {
                railfence[r][c] = teks[count++];
            }
        }
    }

    // ==> memperoleh hasil dekrip
    for (int r = 0, c = 0, d = 1; c < size; r += d, ++c) {
        output += railfence[r][c];
        if (r == kunci - 1) d = -1;
        else if (r == 0) d = 1;
    }
    return output;
}


// ========================== Proses ===========================================================
int main()
{
    // Proses Enkripsi
    cout << "Kriptografi menggunakan algoritma Rail Fence dengan modifikasi  Circular Shift bit dan Kriptografi DNA" << endl;
    cout << "======================== Proses Enkripsi ======================" << endl;
    // 1) Input plain teks dari user
    string teks;
    int kunci;
    cout << "Masukkan plain teks pesan:" << endl;
    getline(cin, teks);
    //cin >> teks;
    
    cout << "Masukkan nilai kunci:"<< endl;
    cin >> kunci;
    //cout << "plain teks anda:" << teks << endl;

    // ======================================================
    // 2) Char ke Decimal ASCII 7-bit (128 karakter)
    int n_char = teks.length();
    vector<int> dec_char(n_char);
    vector<int> temp_dec(n_char);
    for (int x = 0; x<n_char; x++)
    {
        char karakter = teks[x];
        int nilai = int(karakter);

        // === Right Circular shift == (Dari Decimal ASCII)
        int num = nilai;
        int nilai_shift = kunci;
        int result = right_shift_circular(num, nilai_shift);
        int result2 = static_cast<int>(result);

        // === dec_char disimpan
        dec_char[x]= result2;
        temp_dec[x] = nilai;
    }

    
     // ======================================================
    // 3) Dec ke Char
    string char_dec;
    for (int x = 0; x<n_char; x++)
    {
        char karakter2 = char(dec_char[x]);
        char_dec = char_dec + karakter2;
    }
    int n_char2 = char_dec.length();

    // 5) Rail Fence (Enkrip)
    //string teks = char_dec;
    string hasil_enkripsi = enkripsi(char_dec, kunci);
    cout << " " << endl;
    cout << "Jumlah char enkripsi teks:" << n_char2 << endl;
    //cout << "Hasil enkripsi teks :\n" << hasil_enkripsi << endl;
    //cout << "===============================================================" << endl;

    string ciper_dna = "";
    for (int y = 0; y<n_char; y++){
        ciper_dna = ciper_dna + bit_to_dna(hasil_enkripsi[y]);
    }
    cout << "Hasil enkripsi (cipher_text):" << ciper_dna << endl;

    cout << " " << endl;
    // ================== Proses Dekripsi =============================
    cout << "======================== Proses Dekripsi ======================" << endl;

    string ciper_teks_dna;
    cout << "Masukkan ciper teks pesan:" << endl;
    cin >> ciper_teks_dna;
    //getline(cin, ciper_teks_dna);

    int kunci_dekrip;
    cout << "Masukkan nilai kunci:"<< endl;
    cin >> kunci_dekrip;

    // dekrip DNA < =======
    int panjangSetiapLoop = 4;
    int totalLoop = ciper_teks_dna.length() / panjangSetiapLoop;
    string dekrip_dna;
    int n_dna = ciper_teks_dna.length();

    for (int i = 0; i < totalLoop; ++i){
        string potongan = ciper_teks_dna.substr(i * panjangSetiapLoop, panjangSetiapLoop);
        dekrip_dna = dekrip_dna + dna_to_bit(potongan);
    }
    //cout << "dna_dekrip_cipher_text:" << dekrip_dna << endl;
    

    //6) Rail Fence (Dekrip)
    string hasil_dekripsi = dekripsi(dekrip_dna, kunci_dekrip);

    int n_char_dekrip = hasil_dekripsi.length(); // Menyesuaikan jumlah karakter dari hasil dekripsi
    //cout << n_char_dekrip << endl; 

    //7) Char ke Dec
    vector<int> dec_char2(n_char_dekrip);
    for (int x = 0; x<n_char_dekrip; x++)
    {
        char karakter2 = hasil_dekripsi[x];
        int nilai_dekrip = int(karakter2);

        // ================= Left Shift =======================
        int num_dekrip = nilai_dekrip;
        int nilai_shift_dekrip = kunci_dekrip;
        int result3 = left_shift_circular(num_dekrip, nilai_shift_dekrip);
        int result4 = static_cast<int>(result3);

        dec_char2[x]=result4;
    }

    // 8) Dec ke char
    string char_dec_dekrip;
    for (int x = 0; x<n_char_dekrip; x++)
    {
        char karakter_dekrip = char(dec_char2[x]);
        char_dec_dekrip = char_dec_dekrip + karakter_dekrip;
    }

    //9) Hasil Dekripsi ====================================
    cout << " " << endl;
    int n_char3 = char_dec_dekrip.length();
    cout << "Jumlah char dekripsi teks:" << n_char3 << endl;
    cout << "Hasil dekripsi (plain text):" << char_dec_dekrip << endl;

    cout << " " << endl;
    cout << "Selesai" << endl;

    return 0;
}