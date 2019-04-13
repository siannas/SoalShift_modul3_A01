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
  
#### **PENJELASAN**
Pertama-tama masukan semua parameter argumen ke array kita
```c
for (i = 0; i < length; i++){
arr[i] = atoi(argv[i+1]);
}
```

Berikutnya melakukan Sorting pada array
```c
for(j=0;j<length-1;j++){
for (i = 0; i < length-1; i++){
	if(arr[i]<arr[i+1]){
	    temp = arr[i];
	    arr[i] = arr[i+1];
	    arr[i+1] = temp;
	}
}}
```

Terakhir Melakukan pemanggilan threat fungsi factorial
```c
void* factorial(void *arg){
    int num = (int) arg;
    int result;
    
    result = (num<0) ? 0 : 1;

    printf("%d! = ",num);
    while(num > 1){
        result *= num;
        num--;
    }
    printf("%d\n",result);
}
```

### <a name="no2" ></a>Nomor 2
---
#### **PENJELASAN**
Pada implementasi server kami menggunakan 2 thread dengan alamat localhost namun berbeda portnya. kita menggunakan struct server untuk mempermudah dalam pembangunan server.

```c
struct serverInfo{
    int port;
    char *role;
};
```

berikutnya membangun pointer dengan nama `int *barangku` dan kemudian kita buat shared memory-nya.

```c
key_t key = 1234;
pthread_t tid1, tid2;

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
barang = shmat(shmid, NULL, 0);
*barang = 0;
```

pada thread server kita beri kondisi dimana server akan bertindak sebagai penjual atau server pembeli.
```c
...

while(1){
char buffer[1024] = {0};
valread = read( new_socket , buffer, 1024);

if(strcmp(pt->role, "penjual") == 0){
    if(strcmp(buffer, "tambah\n") == 0){
	*barang += 1;
    }
}
else if(strcmp(pt->role, "pembeli") == 0){
    if(strcmp(buffer, "beli\n") == 0){
	if(*barang<1){
	    send(new_socket , (char*)"transaksi gagal" , strlen(hello) , 0 );
	}else{
	    *barang -= 1;
	    send(new_socket , (char*)"transaksi berhasil" , strlen(hello) , 0 );
	}
    }
}
printf("%ssisa : %d\n",buffer, *barang);
}
```

Selanjutnya kita buat file `pembeli.c` yang bertindak sebagai client pembeli. Di dalamnya kita akan membuat socket beserta akan menginput user dan menangkap respon server.

```c
...

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
	printf("\nConnection Failed \n");
	return -1;
}

char say[30];
while(1){
	char buffer[1024] = {0};
	fgets(say, sizeof(say), stdin);
	send(sock , say , strlen(say) , 0 );
	 //printf("say : %sA---\n", say);
	valread = read( sock , buffer, 1024);
	printf("%s\n",buffer );
}
```

Barulah kita membuat file `penjual.c` yang bertindak sebagai client penjual. Di dalamnya hampir sama dengan file pembeli namun ada penambahan yaitu shared memory dan membuat thread yang setiap lima detiknya menampilkan sisa stok barang.

```c
int *barang;

void* showBarang(void* arg){
    while (1)
    {
        sleep(5);
        printf("stok barang : %d\n", *barang);
    }
    
}

int main(){
    ...
    
    key_t key = 1234;
    int err;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    barang = shmat(shmid, NULL, 0);
    
    ...
    
}
```


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
#### **PENJELASAN**
Pada program ini kami menggunakan 2 file yaitu `permainan.c` dan `penjual.c`.<br />
pada program permainan kita inisialisasi semua variabel yang dibutuhkan dan variabel yang akan dibuat shared memory-nya bersama file penjual.
```c
int *value;
char a = '\0';

int health=300;
int hunger=200;
int food_stock = 5;
int hyg=100;
int cd=20;
int eat=0;
int bath = 0;
int aksi = 0;
int turn = 0;
int stop = 0;
int opponent = 100;

key_t key = 1234;
int mem;
struct termios old, new;
```

```c
int main(int argc, char const *argv[]) 
{
    mem = shmget(key,sizeof(int),IPC_CREAT|0666);
    value = shmat(mem,NULL,0);
    
    ...
}
```

berikutnya kita buat beberapa thread dengan fungsinya masing-masing. Program akan berjalan selama nilai `hunger` > 0 , `hygiene` > 0 , `health` > 0, dan flag `stop` = 1.
```c
    pthread_create(&t[0],NULL,input,NULL);
    pthread_create(&t[1],NULL,hunger_status,NULL);
    pthread_create(&t[2],NULL,health_status,NULL);
    pthread_create(&t[3],NULL,hygiene_status,NULL);
    pthread_create(&t[4],NULL,interface,NULL);

    while(hunger>0&&hyg>0&&health>0&&!stop);
```

Ada penambahan fungsi yaitu `getch()` untuk mendapatkan satu input tanpa perlu menekan tombol enter.
```c
char getch() 
{
    char ch;
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    // new.c_lflag |= ECHO; /* set echo mode */
    new.c_lflag &= ~ECHO; /* set no echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
    ch = getchar();
    tcsetattr(0, TCSANOW, &old);
    return ch;
}
```

Berikutnya pada file `penjual.c` kita akan membuat shared memory yang sama dengan di server.
