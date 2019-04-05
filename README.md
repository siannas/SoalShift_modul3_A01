# SoalShift_modul1_A01

index |
--- | 
[nomor 1](#no1) |
[nomor 2](#no2) |
[nomor 3](#no3) |
[nomor 4](#no4) |
[nomor 5](#no5) |

### <a name="no1" ></a>Nomor 1
---
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan  <br />
Contoh: ./faktorial 5 3 4 
  - 3! = 6 
  - 4! = 24 
  - 5! = 120


### <a name="no2" ></a>Nomor 2
---



### <a name="no3" ></a>Nomor 3
---
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan,             sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan          laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan          sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan           ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin           membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering             tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu             program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:<br />
a. Terdapat 2 karakter Agmal dan Iraj <br />
b. Kedua karakter memiliki status yang unik <br />
  - Agmal mempunyai WakeUp_Status, di awal program memiliki status 0 <br />
  - Iraj memiliki Spirit_Status, di awal program memiliki status 100 <br />
  - Terdapat 3 Fitur utama <br />
    - All Status, yaitu menampilkan status kedua sahabat <br />
    - “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point <br />
    - “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point <br />
  - Terdapat Kasus yang unik dimana: <br />
    - Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”) <br />
    - Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”) <br />
  - Program akan berhenti jika Salah Satu : <br />
    - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”) <br />
    - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”) <br />
  - Syarat Menggunakan Lebih dari 1 Thread<br />

#### **PENJELASAN**

berikut global variabel yang dibutuhkan
```c
int status;
int WakeUp_Status = 0;
int Spirit_Status = 100;
int Acount = 0;             // Banyak Fungsi "Agmal Ayo Bangun" dipanggil
int Icount = 0;            // Banyak Fungsi "Iraj Ayo Tidur" dipanggil
```
berikut Fungsi threat Agmal untuk mengecek kondisi, Status, dan akan sleep selama 10 detik ketika Fungsi "Iraj Ayo Tidur" telah dipanggil sebanyak tiga kali.
```c
void* Agmal(void *arg){
    while(status){
        if(WakeUp_Status >= 100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            status = 0;
            return NULL;
        }
        if(Icount == 3){
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            Icount = 0;
        }
    }
    return NULL;
}
```

berikut Fungsi threat Iraj untuk mengecek kondisi, Status, dan akan sleep selama 10 detik ketika Fungsi "Agmal Ayo Bangun" telah dipanggil sebanyak tiga kali.
```c
void* Iraj(void *arg){
    while(status){
        if(Spirit_Status <= 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            status = 0;
            return NULL;
        }
        if(Acount == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            Acount = 0;
        }
    }
    return NULL;
}
```

berikut bagian kode untuk mendapatkan inputan user. jika user mengetikkan "Agmal Ayo Bangun", maka WakeUp_Status ditambah 15. jika user mengetikkan "Iraj Ayo Tidur", maka Spirit_Status dikurang 20. 
```c
while(status){
        fgets(say, sizeof(say), stdin);         //Scan input argumen

        if(strcmp(say, "Agmal Ayo Bangun\n") == 0 && Acount<3){
            Acount++;
            WakeUp_Status += 15;
        }
        else if(strcmp(say, "Iraj Ayo Tidur\n") == 0 && Icount<3){
            Icount++;
            Spirit_Status -= 20;
        }
        else if(strcmp(say, "All Status\n") == 0){
            printf("Agmal WakeUp_Status = %d\nIraj Spirit_Status = %d\n", WakeUp_Status, Spirit_Status);
        }
    }
```

### <a name="no4" ></a>Nomor 4
---
 Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan            (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file               ekstensi .txt yaitu SimpanProses1.txt di direktori /home/Document/FolderProses1 dan        SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file         di kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip          dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu          program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file            KompresProses1.zip dan KompresProses2.zip  Dengan Syarat :  
  - Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan            bersama-sama 
  - Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
  - Ketika Mengekstrak file .zip juga harus secara bersama-sama 
  - Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka          program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali” 
  - Wajib Menggunakan Multithreading
  - Boleh menggunakan system 

#### **PENJELASAN**

Berikut variabel-variabel bertipe string yang akan memudahkan pemanggilan oleh `system`.
```c
int zipnow = 0;

const char *loc []= {
    "/home/vagrant/Documents/FolderProses1/SimpanProses1.txt",
    "/home/vagrant/Documents/FolderProses2/SimpanProses2.txt"
};
const char *dir[] = {
    "/home/vagrant/Documents/FolderProses1/",
    "/home/vagrant/Documents/FolderProses2/"
}; 

const char *file[] = {
    "SimpanProses1.txt",
    "SimpanProses2.txt"
};

const char *zipped[] = {
    "KompresProses1.zip",
    "KompresProses2.zip"
};
```

Berikut fungsi yang akan menjadi threat nantinya untuk membuat file `SimpanProses#.txt` yang berisi 1o baris pertama proses saat ini.
```c
void* createFile(void *arg){
    int num = (int) arg;

    char syn [100] = "ps -aux | head -10 > ";
    strcat(syn, loc[num]);
    system(syn);

    zipnow=1;
}
```

Berikut fungsi yang akan menjadi threat nantinya untuk mengkompresi file `SimpanProses#.txt` menjadi `KompresProses#.zip`.
```c
void* zipper(void *arg){
    while(zipnow != 1){}

    char syn [100];
    int num = (int) arg;
    
    sprintf(syn,"zip -m %s %s", zipped[num], file[num]);
    chdir(dir[num]);
    system(syn);

}
```

Berikut fungsi yang akan menjadi threat nantinya untuk mengekstraksi file dari dalam `KompresProses#.zip`.
```c
void* unzipper(void *arg){
    while(zipnow != 1){}

    char syn [100];
    int num = (int) arg;
  
    sprintf(syn,"unzip %s %s", zipped[num], file[num]);
    chdir(dir[num]);
    system(syn);
}
```

Pada proses `pthread_create` antara threat `zipper` dan `unzipper` kita beri selang waktu 15 detik;
```c
...

	sleep(15);
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");

...
```

### <a name="no5" ></a>Nomor 5
---
Buatlah sebuah script bash untuk menyimpan record dalam syslog yang memenuhi
kriteria berikut
