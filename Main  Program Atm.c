/*	Program		: ATM(Auto Teller Machine).c
	Deskripsi	: Program Simulator ATM
	Kelompok	: 9
	Kelas		: 1B
	Anggota		:
			  - Keanu Rayhan Harist (221524043)
			  - Mahardika Pratama (221524044)
			  - Reza Maulana Aziiz (221524057)
	Tanggal		: 14 Desember 2022
	Compiler 	: TDM-GCC 9.2.0 64-bit Release
	===============================================*/
	
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<unistd.h>

//Type Data Bentukan
typedef struct{
	int day, month, years;
}Date;

typedef struct{
	char NoRek[100][10];
	char NamaUser[100][30];
	char NamaBank[100][10];
	int sizeTransaksi;
	int nominal[100];
	int transaksi[100];
	int k;
}Mutasi;

typedef struct{
	int limit_penarikan;
	int limit_transfer;
	int limit_setor;
}limit;

//Data Nasabah
typedef struct{
	char No_Rekening[10];
   	char Nama[30];
   	char Pin[7];
	char Bank[10];
	int total_saldo;
	Date Tanggal_Lahir;
	char Status[7];
	Mutasi Riwayat;
	limit batas;
}Nasabah;
	



//Deklarasi Modul

int validasi_tanggal(int hari, int bulan, int tahun);
//function untuk mengembalikan nilai benar =1 jika tanggal yang diinputkan sesuai dengan tanggal yang ada(kalender), sebaliknya akan mengembalikan nilai benar=0, jika tanggal yang diinputkan tidak sesuai kalender.

int validasi_pin(char pin[7]);
//fungsi untuk mengembalikan nilai benar =1 jika pin yang diinput benar 6 digit, sebaliknya akan mengembalikan nilai benar =0 jika pin yang diinput tidak 6 digit


int cekvaliditasAkun(char No_Rek[10]);
// Fungsi untuk mengembalikan nilai valid=1 jika No_Rek dari akun sudah terdaftar, akan mengembalikan valid=0 jika akun belum terdaftar

void menuBahasa();
/* Prosedur untuk memilih bahasa yang akan digunakan oleh user
	I.S : User belum memilih bahasa yang akan digunakan
	F.S : User sudah memilih bahasa yang akan digunakan
	*/

void enableKartu(int bhs, char inputPin[7]);
/*Prosedur untuk meng-enable kartu jika kartu ATM ter-disable yang disebabkan karena salah menginputkan PIN ATM lebih dari tiga kali
	I.S: Kartu ATM user ter-disable
	F.S: Kartu ATM user sudah ter-enable
	*/	
int validasi_TanggalLahir(int hari, int bulan, int tahun, int *i, int bhs, char inputPin[7]);
//function untuk mengembalikan nilai betul=1 jika tanggal lahir yang diinputkan sesuai dengan tanggal lahir yang diinputkan saat register, sebaliknya akan mengembalikan nilai betul =0 jika tanggal lahir yang diinputkan tidak sesuai 
void MasukkanPin(int bhs); 
/* Prosedur untuk meminta user untuk masuk ke menu masukkan pin
	I.S : User belum menginputkan PIN atm
	F.S : User sudah menginputkan PIN atm 
	*/
	
void bacaPin(char inputPin[7]); 
/*Prosedur untuk membaca input PIN
	I.S: User belum mengetikkan PIN dari keyboard
	F.S: User sudah mengetikkan PIN dari keyboard
	*/

int Cek_validitas( char inputPin[7], int Valid, int *i); 
/*Fungsi untuk mengembalikan nilai benar = 1 jika pin yang di input sesuai dengan pin user. Dan akan mengembalikan nilai benar = 0 jika pin yang di input tidak sesuai dengan pin user
	*/
	
void MenuPenarikanCepat(int bhs, char inputPin[7]); 
/* Prosedur untuk modul fitur Penarikan Cepat
	I.S: User belum memilih nominal yang ada pada fitur penarikan cepat 
	F.S: User sudah memilih nominal yang ada pada fitur penarikan cepat 
	*/

int validitasTransaksi(int bhs, char inputPin[7]);
/* Fungsi untuk mengembalikan nilai Valid jika jumlah transaksi sesuai dengan aturan yaitu saldo sisa transaksi >= Rp.10000 dan limit penarikan<= Rp.10000000
	*/

void MenuJumlahLain(int bhs, char inputPin[7]); 
/* Prosedur untuk menu fitur Jumlah Lain
	I.S: User belum menginputkan nominal jumlahlain
	F.S: User sudah menginputkan nominal jumlahlain
	*/

void bacaJumlahLain(); 
/*Prosedur untuk membaca input jumlah nominal yang akan ditarik
	I.S: User belum mengetikkan  jumlah nominal yang lain dari keyboard
	F.S: User sudah mengetikkan  jumlah nominal yang lain dari keyboard
	*/

void MenuLainnya(int bhs, char inputPin[7]); 
/*Prosedur untuk modul fitur Menu Lainnya
	I.S: User belum memilih fitur Menu Lainnya
	F.S: User sudah memilih fitur Menu Lainnya
	*/

void MenuTransfer(int bhs, char inputPin[7]);
/* Prosedur untuk modul fitur Menu Transfer
	I.S: User belum memilih fitur Menu Transfer
	F.S: User sudah memilih fitur Menu Transfer
	*/
	
void konfirmasitrf(int bhs, char inputPin[7]);
/* Prosedur konfirmasi menampilkan data validitas transaksi transfer
	I.S: User belum melihat data validitas transaksi transfer
	F.S: User sudah melihat data validitas transaksi transfer
	*/

void MenuKonfirmasi(int bhs, char inputPin[7]); 
/* Prosedur konfirmasi dari proses transfer 
	I.S: User belum melakukan konfirmasi transfer
	F.S: User sudah melakukan konfirmasi transfer dengan kembali ke menu selanjutnya
	*/

int cek_ValiditasNorek(int bhs, char No_Rek[10]);
/* Fungsi untuk mengembalikan nilai benar = 1 jika No. Rekening tujuan yang diinput sama dengan data no.rekening penerima. Dan akan mengembalikan nilai 0 jika sebaliknya
	*/

int cek_ValiditasTransfer(int admin);
/* Fungsi untuk mengembalikan nilai benar = 1 jika transaksi memenuhi aturan yaitu limit transfer Rp. 10000000 dan sisa saldo minimum yang ada Rp. 10000. Dan akan mengembalikan nilai 0 jika sebaliknya.
	*/

void Menu_setor(int bhs, char inputPin[7]);
/* Prosedur untuk modul fitur Setor Tunai
	I.S: User belum melakukan Setor Tunai
	F.S: User sudah melakukan Setor Tunai
	*/
	
int cekvalid_setor();	
/* Fungsi untuk mengembalikan nilai betul= 1 jika transaksi memenuhi aturan yaitu limit setor Rp. 5000000 dan nomminal kelipatan Rp. 50000. Dan akan mengembalikan nilai 0 jika sebaliknya.
	*/

void bacasetorlagi(int bhs, char inputPin[7]);
/*prosedur untuk menampilkan pilihan setor lagi atau tidak
	I.S : User belum melakukan pilihan setor lagi atau tidak 
	F.S : User sudah melakukan pilihan setor lagi atau tidak 
	*/

void displayGagalMin(int bhs);
/*prosedur untuk menampilkan tampilan gagal karena tidak memenuhi nominal minimum
	I.S : Tampilan untuk tampilan gagal karena tidak memenuhi nominal minimum belum tercetak
	F.S : Tampilan untuk tampilan gagal karena tidak memenuhi nominal minimum sudah tercetak
	*/

void MenuInformasiSaldo(int bhs, char inputPin[7]);
/* Prosedur untuk modul dari fitur Menu Informasi Saldo
	I.S: User belum melakukan fitur Menu Informasi Saldo
	F.S: User sudah melakukan fitur Menu Informasi Saldo
	*/
	

void MenuUbahPin(int bhs, char inputPin[7]);
/* Prosedur untuk modul dari fitur Menu Ubah PIN
	I.S: User belum mengubah PIN
	F.S: User sudah mengubah PIN
	*/

void InputPinLama(int bhs, char inputPin[7]);
/* Prosedur untuk modul memasukkan PIN Lama
	I.S: User belum menginput dan cek validitas pin lama
	F.S: User sudah menginput dan cek validitas PIN lama
	*/
	
void bacaKonfirmasiPinBaru(char konfirmasiPin[7], int bhs);
/* Prosedur untuk menginput konfirmasi PIN Baru
	I.S: User belum menginput konfirmasi PIN Baru 
	F.S: User sudah menginput konfirmasi PIN Baru 
	*/
	
int Cek_validitasPinBaru(char inputPinBaru[7], char konfirmasiPin[7], int *i, int bhs, char inputPin[7]);
/*Fungsi untuk mengembalikan nilai benar = 1 jika pin yang di input sesuai dengan pin user. Dan akan mengembalikan nilai benar = 0 jika pin yang di input tidak sesuai dengan pin user
	*/
	
void MasukkanPinBaru(int bhs, char inputPin[7]);
/* Prosedur untuk modul perintah menginput PIN Baru
	I.S: User belum menginput dan cek validitas PIN Baru
	F.S: User sudah menginput dan cek validitas PIN Baru
	*/

void LihatMutasi(int bhs);
/*prosedur untuk menampilkan mutasi rekening
	I.S : User belum melihat mutasi
	F.S : User sudah melihat mutasi
	*/
	
void gotoxy(int x, int y);
/*Prosedur ini berfungsi untuk menentukan kordinat pada tampilan atm 
	I.S : koordinat untuk menentukan tampilan display belum tebentuk
	F.S : koordinat untuk menentukan tampilan dispaly sudah terbentuk
	*/

void printToxy(int x, int y, char* label);
/*prosedur untuk menampilkan suatu inputan sesuai koordinat 
	I.S : Inputan belum tercetak
	F.S : Inputan sudah tercetak
	*/

void header();
/*prosedur untuk mencetak dan menampilkan bagian header pada atm  
	I.S : Header ATM belum tercetak
	F.S : Header ATM sudah tercetak
	*/

void displayLoginAtm();
/* prosedur untuk menampilkan tampilan Login ATM
	I.S : Tampilan Login ATM belum tercetak
	F.S : Tampilan Login ATM sudah tercetak
	*/

void displayBacaKartu();
/* prosedur untuk menampilkan tampilan register
	I.S : Tampilan untuk register kartu belum tercetak
	F.S : Tampilan untuk register kartu sudah tercetak
	*/

void displayTidakTerdaftar();
/* Prosedur untuk menampilkan tampilan jika nomor rekening tidak terdaftaf saat log in
	I.S : Tampilan untuk nomor rekening tidak terdaftar belum tercetak 
	F.S : Tampilan untuk nomor rekening tidak terdaftar sudah tercetak 
	*/

void displayMenuBahasa();
/*prosedur untuk menampilkan tampilan menu pilih bahasa
	I.S : Tampilan menu bahasa belum tercetak
	F.S : Tampilan menu bahasa sudah tercetak
	*/

void displayMenuPinId(int bhs);
/*prosedur untuk menampilkan tampilan menu pin
	I.S : Tampilan menu PIN belum tercetak
	F.S : Tampilan menu PIN sudah tercetak
	*/

void displaySalahPin(int bhs);
/*prosedur untuk menampilkan tampilan jika terdapat kesalahan dalam menginput pin
	I.S : Tampilan menu pin jika salah belum terbentuk
	F.S : Tampilan menu pin jika salah sudah terbentuk
	*/

void displayAkunTerblokir(int bhs);
/*prosedur untuk menampilkan tampilan jika input kesalahan pin lebih dari tiga kali
	I.S : Tampilan jika akun terblokir belum tercetak
	F.S : Tampilan jika akun terblokir sudah tercetak
	*/

void displayMenuPenarikanCepat(int bhs);
/*prosedur untuk menampilkan tampilan pada menu penarikan cepat
	I.S : Tampilan untuk menu penarikan cepat belum tercetak
	F.S : Tampilan untuk menu penarikan cepat sudah tercetak
	*/

void displayTransaksiBerhasil(int bhs);
/*prosedur untuk menampilkan tammpilan jika transaksi berhasil
	I.S : Tampilan jika transaksi belum tercetak
	F.S : Tampilan jika transaksi berhasil sudah tercetak
	*/

void displayTransaksiGagal(int bhs);
/*prosedur untuk menampilkan tampilan jika transaksi gagal
	I.S : Tampilan untuk transaksi gagal belum tercetak
	F.S : Tampilan untuk transaksi gagal sudah tercetak
	*/

void displayTransaksiGagallimit(int bhs);
/*prosedur untuk menampilkan tampilan jika transaksi melebihi limit batas perhari
	I.S : Tampilan transaksi gagal karena limit belum tercetak
	F.S : Tampilan transaksi gagal karena limit sudah tercetak
	*/

void displayMenuJumlahLain(int bhs);
/*prosedur untuk menampilkan tampilan jika user ingin menarik uang dalam jumlah lain 
	I.S : Tampilan menu jumlah lain belum tercetak
	F.S : Tampilan menu jumlah lain sudah tercetak
	*/

void displayLoading(int bhs);
/*prosedur untuk menampilkan jeda loading pada setiap transaksi
	I.S : Tampilan jeda loading pada setiap transaksi belum tercetak
	F.S : Tampilan jeda loading pada setiap transaksi sudah tercetak
	*/

void displayEnd(int bhs);
/*prosedur untuk menampilkan tampilan ucapan terima kasih pada setiap akhir transaksi 
	I.S : Tampilan dispalyEnd belum tercetak
	F.S : Tampilan displayEnd sudah tercetak
	*/

void displayMenuLainnya(int bhs);
/*prosedur untuk meampilkan tampilan jumlah lainnya selain dari menu penarikan cepat
	I.S : Tampilan menu lainnya belum tercetak
	F.S : Tampilan menu lainnya sudah tercetak
	*/

void displayMenuTransfer(int bhs);
/*prosedur untuk menampilkan tampilan menu transfer
	I.S : Tampilan menu transfer belum tercetak
	F.S : Tampilan menu transfer sudah tercetak
	*/

void displayNo_RekNull(int bhs);
/* Prosedur untuk menampilkan tampilan jika nomor rekening saat transfer tidak ada/salah
	I.S : Tampilan nomor rekening salah/tidak ada belum tercetak
	I.S : Tampilan nomor rekening salah/tidak ada sudah tercetak
	*/

void displayProsesTransfer(int bhs);
/*prosedur untuk menampilkan tampilan jika proses transfer berlangsung
	I.S : Tampilan proses transfer belum tercetak
	F.S : Tampilan proses transfer sudah tercetak
	*/

void displaytransfergagal(int bhs);
/*prosedur untuk menampilkan tampilan jika transfer gagal dilakukan
	I.S : Tampilan jika transfer gagal belum tercetak
	F.S : Tampilan jika transfer gagal sudah tercetak
	*/

void displaytransferberhasil(int bhs);
/*prosedur untuk menampilkan tampilan jika tranfer berhasil dilakukan
	I.S : Tampilan jika transfer berhasil belum tercetak
	F.S : Tampilan jika transfer berhasil sudah tercetak
	*/

void displaykonfirmasitrf(int bhs,int admin);
/*prosedur untuk menampilkan tampilan konfirmasi transfer
	I.S : Tampilan untuk konfirmasi transfer belum tercetak
	F.S : Tampilan untuk konfifmasi transfer sudah tercetak
	*/

void displaygoodtransfer(int bhs);
/*prosedur untuk menampilkan tampilan jika transaksi selesai dan menanyakan kembali apakah user ingin transfer lagi
	I.S : Tampilan transaksi selesai belum tercetak
	F.S : Tampilan transaksi selesai sudah tercetak
	*/

void displayInformasiSaldo(int bhs);
/*prosedur untuk menampilkan tampilan Informasi Saldo
	I.S : Tampilan untuk Informasi Saldo belum tercetak
	F.S : Tampilan untuk Informasi Saldo sudah tercetak
	*/

void displayUbahPinLama(int bhs);
/*prosedur untuk menampilkan tampilan meminta input pin lama
	I.S : Tampilan untuk tampilan meminta input pin lama belum tercetak
	F.S : Tampilan untuk tampilan meminta input pin lama sudah tercetak
	*/

void displayMenuSetor(int bhs);
/*prosedur untuk menampilkan menu setor tunai
	I.S : Tampilan untuk menu setor tunai belum tercetak
	F.S : Tampilan untuk menu setor tunai sudah tercetak
	*/


void displaysetorberhasil(int bhs);
/*prosedur untuk menampilkan setoran berhasil
	I.S : Tampilan untuk setoran berhasil belum tercetak
	F.S : Tampilan untuk setoran berhasil sudah tercetak
	*/

void displayPinBaru(int bhs);
/*prosedur untuk menampilkan tampilan meminta input pin baru
	I.S : Tampilan untuk tampilan meminta input pin baru belum tercetak
	F.S : Tampilan untuk tampilan meminta input pin baru sudah tercetak
	*/

void displaySalahMengubahPin(int bhs);
/*prosedur untuk menampilkan pin yang dimasukkan salah
	I.S : Tampilan untuk pin yang dimasukkan salah belum tercetak
	F.S : Tampilan untuk pin yang dimasukkan salah sudah tercetak
	*/

void displayUbahPinBerhasil(int bhs);
/*prosedur untuk menampilkan berhasil mengubah pin
	I.S : Tampilan untuk berhasil mengubah pin belum tercetak
	F.S : Tampilan untuk berhasil mengubah pin sudah tercetak
	*/

void displayUbahPinGagal(int bhs);
/*prosedur untuk menampilkan berhasil mengubah pin
	I.S : Tampilan untuk gagal mengubah pin belum tercetak
	F.S : Tampilan untuk gagal mengubah pin sudah tercetak
	*/
void displaySaldoAtmHabis(int Bhs);
//

void displaykonfirmasiPin(int bhs);
/*prosedur untuk menampilkan permintaan konfirmasi pin baru
	I.S : Tampilan untuk permintaan konfirmasi pin baru belum tercetak
	F.S : Tampilan untuk permintaan konfirmasi pin baru sudah tercetak
	*/

void cetakMutasi(int bhs,int *i);
/*prosedur untuk menampilkan riwayat mutasi rekening
	I.S : Tampilan untuk riwayat mutasi rekening belum tercetak
	F.S : Tampilan untuk riwayat mutasi rekeningpermintaan konfirmasi pin baru sudah tercetak
	*/

void displaybuatakun();
/*Prosedur untuk membuat kartu(akun) untuk user baru(register)
	 I.S: Kartu belum didaftarkan
	 F.S: Kartu sudah didaftarkan
	 */
  
void displayAkunBerhasil();
/*Prosedur untuk menampilkan jika kartu berhasil diregister
	 I.S: tampilan untuk kartu berhasil diregister belum ditampilkan
	 F.S: tampilan untuk kartu berhasil diregister sudah ditampilkan
	 */
  
void displayAkunDisable(int bhs);
/*Prosedur untuk menampilkan jika kartu ter-disable
	 I.S: tampilan untuk kartu ter-disable belum ditampilkan
	 F.S: tampilan untuk kartu ter-disable sudah ditampilkan
	 */
 
void displayEnableTanggalLahir(int bhs);
 /*Prosedur untuk menampilkan jika kartu ingin di-enable
	 I.S: tampilan untuk enable kartu belum ditampilkan
	 F.S: tampilan untuk enable kartu sudah ditampilkan
	 */
void displayEnableTanggalLahirSalah3x(int bhs);
/*Prosedur untuk menampilkan jika salah menginputkan tanggal lahir lebih dari 3 kali
	 I.S: tampilan untuk kesalahan input tanggal lahir belum ditampilkan
	 F.S: tampilan untuk kesalahan input tanggal lahir sudah ditampilkan
	 */
void displayEnableBerhasil(int bhs);
/*Prosedur untuk menampilkan jika kartu berhasil di-enable
	 I.S: tampilan untuk kartu berhasil di-enable belum ditampilkan
	 F.S: tampilan untuk kartu berhasil di-enable sudah ditampilkan
	 */
void displayEnableGagal(int bhs);
/*Prosedur untuk menampilkan jika kartu gagal di-enable
	 I.S: tampilan untuk kartu jika gagal di-enable belum ditampilkan
	 F.S: tampilan untuk kartu jika gagal di-enable sudah ditampilkan
	 */
void displayEnable(int bhs);
/*Prosedur untuk menampilkan tampilan enable kartu
	 I.S: tampilan untuk enable kartu belum ditampilkan
	 F.S: tampilan untuk enable kartu sudah ditampilkan
	 */

//Deklarasi variabel Global

//Inisialisasi Data User
Nasabah user[100] = {
			{.No_Rekening="221524044",.Nama="Mahardika",.Pin="123456",.Bank = "BRI", .total_saldo=20000000, .Tanggal_Lahir.day =17, .Tanggal_Lahir.month = 8, .Tanggal_Lahir.years =2003, .Status = "ENABLE", .Riwayat.sizeTransaksi = 0, .Riwayat.k = 0, .batas.limit_penarikan = 0, .batas.limit_transfer = 0, .batas.limit_setor = 0},
			{.No_Rekening="221524043",.Nama="Keanu",.Pin="111111",.Bank = "BCA", .total_saldo=5000000, .Tanggal_Lahir.day =31, .Tanggal_Lahir.month = 07, .Tanggal_Lahir.years =2004, .Status = "ENABLE", .Riwayat.sizeTransaksi = 0, .Riwayat.k = 0, .batas.limit_penarikan = 0, .batas.limit_transfer = 0, .batas.limit_setor = 0},    
			{.No_Rekening="221524057",.Nama="Reza",.Pin="123123",.Bank = "BRI", .total_saldo=50000, .Tanggal_Lahir.day =24, .Tanggal_Lahir.month = 05, .Tanggal_Lahir.years =2004, .Status = "DISABLE", .Riwayat.sizeTransaksi = 0, .Riwayat.k = 0, .batas.limit_penarikan = 0, .batas.limit_transfer = 0, .batas.limit_setor = 0},
		};                                                                                                                                                                                       
			
//variabel untuk index user
int j;
//variabel untuk index penerima
int r;
//variabel global untuk data uang atm
int saldo_ATM = 50000000;
/*Algoritma*/

//Main Program
int main(){
	int i, z, t;
	int opsi;
	int benar;
	char No_Rek[10];
	char Nama[30];
	char inputPin [7];
	char Bank[10];
	int hari, bulan, tahun;
	
	system ("color 1F"); //syntak untuk mengubah warna di cmd
	system("cls");
	displayLoginAtm();
	i = 1;
	benar = 0;
	scanf("%d",&opsi);
	switch(opsi){
		case 4 : 
			system("cls");
			displayBacaKartu();
			BACA:
			scanf ("%s", No_Rek);
			benar = cekvaliditasAkun(No_Rek);
			if (benar == 1){
				menuBahasa();
			}
			else {
				system("cls");
				displayTidakTerdaftar();
				goto BACA;
			}
			break;
		case 5 : 
			Label2:
			system("cls");
			displaybuatakun();
			t = sizeof(user)/sizeof(user[0]);
			gotoxy(60,9);
			printf("Masukkan No.Rek :");
			scanf ("%s", No_Rek);
			gotoxy(60,10);
			printf("Masukkan Nama Anda: ");
			scanf ("%s", Nama);
			gotoxy(60,11);
			printf("Masukkan Pin Anda: ");
			scanf ("%s", inputPin);
			benar = validasi_pin(inputPin);
			if (benar == 1){
				gotoxy(60,12);
				printf("Masukkan Bank Anda: ");
				scanf ("%s", Bank);
				gotoxy(60,13);
				printf("Masukkan Tanggal Lahir Anda: ");
				scanf ("%d %d %d", &hari, &bulan, &tahun);
				benar = validasi_tanggal(hari, bulan, tahun);
				if (benar == 1){
					for (int i=0; i<t; i++){
						while (user[i].total_saldo == 0){
							strcpy (user[i].No_Rekening, No_Rek);
							strcpy (user[i].Nama, Nama);
							strcpy (user[i].Pin,inputPin);
							strcpy (user[i].Bank, strupr(Bank));
							user[i].total_saldo = 100000;
							user[i].Tanggal_Lahir.day = hari;
							user[i].Tanggal_Lahir.month = bulan;
							user[i].Tanggal_Lahir.years = tahun;
							user[i].Riwayat.sizeTransaksi = 0;
							user[i].batas.limit_penarikan = 0;
							user[i].batas.limit_transfer = 0;
							user[i].batas.limit_setor = 0;
							strcpy (user[i].Status,"ENABLE");
							z = 1;
							break;
						}
						j = i;
						if (z == 1){
							system("cls");
							displayAkunBerhasil();
							sleep(5);
							break;
						}
					}
				}
				else{
					gotoxy(60,14);
					printf("Pastikan Tanggal Lahir yang Anda");
					gotoxy(60,15);
					printf("Masukkan Valid !!!");
					sleep(3);
					goto Label2;
				}
			}
			else{
				gotoxy(60,12);
				printf("Pastikan Pin Anda 6 digit");
				sleep(3);
				goto Label2;
			}
		default : 
			main();
	}
}

int validasi_tanggal(int hari, int bulan, int tahun){
	int benar;
	if (hari<=31 && bulan<=12 && bulan!= 2){
		benar = 1;
	}
	else if (hari<=29 && bulan== 2){
		benar = 1;
	}
	else{
		benar = 0;
	}
	return benar;
}

int validasi_pin(char pin[7]){
	int benar;
	if (strlen(pin)==6){
		benar = 1;
	}
	else{
		benar = 0;
	}
	return benar;
}

int cekvaliditasAkun(char No_Rek[10]){
	int Valid;
	int a = 0;
	while (user[a].total_saldo != 0){
		if(strcmp(No_Rek, user[a].No_Rekening)==0){
			Valid = 1;
			j = a;
			break;
		}
		else{
			Valid = 0;
		}
		a = a + 1;
	}
	return Valid;
}

	
void menuBahasa(){
	int bahasa;
	int opsi;
	system("cls");
	displayMenuBahasa();	
   	scanf("%d",&opsi);
    	switch(opsi){
    		case 4: 
			bahasa = 1; // bahasa indonesia
			system ("cls");
    			MasukkanPin(bahasa);  //	Memanggil modul memasukkan pin
			break;
   		case 5: 
			bahasa = 2;// bahasa inggris
		   	system ("cls");		
    			MasukkanPin(bahasa);	
    			break;
    		default :
        		menuBahasa();
    	}
}

//Modul Bahasa Indonesia
void MasukkanPin(int bhs){
	int i;
	int benar;
	char inputPin[7];
	
	benar = 0;
	i = 1;
	displayMenuPinId(bhs); //Memanggil modul menu pin
	while(benar == 0 && i<=3){
		bacaPin(inputPin); //Memanggil modul baca pin
		benar = Cek_validitas(inputPin, bhs, &i); //Memanggil modul cek validitas pin
	}
	if (benar == 1){
		MenuPenarikanCepat(bhs, inputPin ); //Memanggil modul penarikan cepat
	}
}

//Modul baca pin
void bacaPin(char inputPin[7]){
	int i;
	gotoxy(53, 13);
    	for(i = 0; i < 6; i++){
		inputPin[i] = _getch();
		putchar('*');
		putchar(' ');
    }
}

//Modul cek validitas pin
int Cek_validitas(char inputPin[7], int bhs, int *i){
	int IsValid;
	
	if(strcmp(inputPin, user[j].Pin)==0){
		IsValid = 1;
	}
	else if(*i<3){
		*i = *i + 1;
		IsValid = 0;
		system("cls");
		displaySalahPin(bhs); //Memanggil modul displaySalahPin();
	}
	else{
		strcpy(user[j].Status, "DISABLE");
		system("cls");
		displayAkunTerblokir(bhs); //Memanggil modul displayAkunTerblokir();
		sleep(5);
		main();
	}
	return IsValid;
}

//Modul Menu Penarikan Cepat
void MenuPenarikanCepat(int bhs, char inputPin[7]){
	int benar;
	int opsi;
	char konfirmasi;
	
	KEMBALI:
	system("cls");
	displayMenuPenarikanCepat(bhs); //Memanggil modul displayMenuPenarikanCepat();
	benar = 0;
	scanf("%d", &opsi);
	switch(opsi){
		case 1: 
			if (strcmp(user[j].Status, "ENABLE")==0){
				user[j].Riwayat.nominal[user[j].Riwayat.k] = 250000;
				user[j].batas.limit_penarikan = user[j].batas.limit_penarikan + user[j].Riwayat.nominal[user[j].Riwayat.k];
				benar = validitasTransaksi(bhs, inputPin); //Memanggil modul validitasTransaksi
				if (benar == 1){
					user[j].total_saldo = user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k];
					system("cls");
					displayLoading(bhs); //Memanggil modul displayLoading();
					sleep(5);
					system("cls");
					displayTransaksiBerhasil(bhs); //Memanggil modul displayTransaksiBerhasil();
					saldo_ATM = saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k];
			
					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
					user[j].Riwayat.transaksi[user[j].Riwayat.k] = 1;
					user[j].Riwayat.k = user[j].Riwayat.k + 1;
	    			
					GO:
					gotoxy(88, 24);
					konfirmasi = getch();
					switch(konfirmasi){
						case '5' : 
							goto KEMBALI;
							break;
						case '6' : 	
							system("cls");
							displayEnd(bhs); //Memanggil modul displayEnd();
							sleep(5);
							main();
						default:
							goto GO;
					}
				}
			}
			else if(strcmp(user[j].Status, "DISABLE")==0){
				system("cls");
				displayLoading(bhs); 
				sleep(5);
				system("cls");
				displayAkunDisable(bhs);
				DO1:
				gotoxy(88, 24);
				konfirmasi = getch();
				switch(konfirmasi){
					case '5' : 
						enableKartu(bhs,inputPin);
						break;
					case '6' : 	
						system("cls");
						displayEnd(bhs); //Memanggil modul displayEnd();
						sleep(5);
						MenuPenarikanCepat(bhs, inputPin);
					default:
						goto DO1;
				}
			}
			break;
		case 2: 
			if (strcmp(user[j].Status, "ENABLE")==0){
				system("cls");
				user[j].Riwayat.nominal[user[j].Riwayat.k]= 500000;
				user[j].batas.limit_penarikan = user[j].batas.limit_penarikan + user[j].Riwayat.nominal[user[j].Riwayat.k];
				benar = validitasTransaksi(bhs, inputPin); //Memanggil modul validitasTransaksi
				if (benar == 1){
					user[j].total_saldo = user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k];
					system("cls");
					displayLoading(bhs); //Memanggil modul displayLoading();
					sleep(5);
					system("cls");
					displayTransaksiBerhasil(bhs); //Memanggil modul displayTransaksiBerhasil();
					saldo_ATM = saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k];
						
					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
					user[j].Riwayat.transaksi[user[j].Riwayat.k] = 1;
					user[j].Riwayat.k = user[j].Riwayat.k + 1;
	    				
					GO4:
					gotoxy(88, 24);
					konfirmasi = getch();
					switch(konfirmasi){
						case '5' : 
							goto KEMBALI;
							break;
						case '6' : 	
							system("cls");
							displayEnd(bhs); //Memanggil modul displayEnd();
							sleep(5);
							main();
						default:
							goto GO4;
					}
				}
			}
			else if(strcmp(user[j].Status, "DISABLE")==0){
				system("cls");
				displayLoading(bhs); 
				sleep(5);
				system("cls");
				displayAkunDisable(bhs);
				DO2:
				gotoxy(88, 24);
				konfirmasi = getch();
				switch(konfirmasi){
					case '5' : 
						enableKartu(bhs,inputPin);
						break;
					case '6' : 	
						system("cls");
						displayEnd(bhs); //Memanggil modul displayEnd();
						sleep(5);
						MenuPenarikanCepat(bhs, inputPin);
					default:
						goto DO2;
				}
			}
			break;
		case 3:	
			if (strcmp(user[j].Status, "ENABLE")==0){
				system("cls");
				user[j].Riwayat.nominal[user[j].Riwayat.k] = 1000000;
				user[j].batas.limit_penarikan = user[j].batas.limit_penarikan + user[j].Riwayat.nominal[user[j].Riwayat.k];
				benar = validitasTransaksi(bhs, inputPin); //Memanggil modul validitasTransaksi
				if (benar == 1){
					user[j].total_saldo = user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k];
					system("cls");
					displayLoading(bhs); //Memanggil modul displayLoading();
					sleep(5);
					system("cls");
					displayTransaksiBerhasil(bhs); //Memanggil modul displayTransaksiBerhasil();
					saldo_ATM = saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k];
						
					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
					user[j].Riwayat.transaksi[user[j].Riwayat.k] = 1;
					user[j].Riwayat.k = user[j].Riwayat.k + 1;
	    				
					GO7:
					gotoxy(88, 24);
					konfirmasi = getch();
					switch(konfirmasi){
						case '5' : 
							enableKartu(bhs,inputPin);
							break;
						case '6' : 	
							system("cls");
							displayEnd(bhs); //Memanggil modul displayEnd();
							sleep(5);
							MenuPenarikanCepat(bhs, inputPin);
						default:
							goto GO7;
					}
				}
			}
			else if(strcmp(user[j].Status, "DISABLE")==0){
				system("cls");
				displayLoading(bhs); 
				sleep(5);
				system("cls");
				displayAkunDisable(bhs);
				DO3:
				gotoxy(88, 24);
				konfirmasi = getch();
				switch(konfirmasi){
					case '5' : 
						enableKartu(bhs, inputPin);
						break;
					case '6' : 	
						system("cls");
						displayEnd(bhs); //Memanggil modul displayEnd();
						sleep(5);
						MenuPenarikanCepat(bhs, inputPin);
					default:
						goto DO3;
				}
			}
			break;
		case 4: 
			if (strcmp(user[j].Status, "ENABLE")==0){
				system("cls");
				user[j].Riwayat.nominal[user[j].Riwayat.k] = 1250000;
				user[j].batas.limit_penarikan = user[j].batas.limit_penarikan + user[j].Riwayat.nominal[user[j].Riwayat.k];
				benar = validitasTransaksi(bhs, inputPin); //Memanggil modul validitasTransaksi
				if (benar == 1){
					user[j].total_saldo = user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k];
					system("cls");
					displayLoading(bhs); //Memanggil modul displayLoading();
					sleep(5);
					system("cls");
					displayTransaksiBerhasil(bhs); //Memanggil modul displayTransaksiBerhasil();
					saldo_ATM = saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k];
						
					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
					user[j].Riwayat.transaksi[user[j].Riwayat.k] = 1;
					user[j].Riwayat.k = user[j].Riwayat.k + 1;
	    		
					GO10:
					gotoxy(88, 24);
					konfirmasi = getch();
					switch(konfirmasi){
						case '5' : 
							goto KEMBALI;
							break;
						case '6' : 	
							system("cls");
							displayEnd(bhs); //Memanggil modul displayEnd();
							sleep(5);
							main();
						default:
							goto GO10;
					}
				}
			}
			else if(strcmp(user[j].Status, "DISABLE")==0){
				system("cls");
				displayLoading(bhs); 
				sleep(5);
				system("cls");
				displayAkunDisable(bhs);
				DO4:
				gotoxy(88, 24);
				konfirmasi = getch();
				switch(konfirmasi){
					case '5' : 
						enableKartu(bhs,inputPin);
						break;
					case '6' : 	
						system("cls");
						displayEnd(bhs); //Memanggil modul displayEnd();
						sleep(5);
						MenuPenarikanCepat(bhs, inputPin);
					default:
						goto DO4;
				}
			}	
			break;
		case 5: 
			system("cls");
			MenuJumlahLain(bhs,inputPin); //Memanggil Modul MenuJumlahLain();
			break;
		case 6: 
			MenuLainnya(bhs, inputPin); //Memanggil Modul MenuLainnya();
			break;
		case 99: 
			main();
		       	break;		
				
		default:
			goto KEMBALI;
	}
}

//Modul Jumlah Lain
void MenuJumlahLain(int bhs, char inputPin[7]){
	char konfirmasi;
	int benar;
	int opsi;
	BACK:
	system("cls");
	displayMenuJumlahLain(bhs); //Memanggil modul untuk tampilan menu jumlah lain
	bacaJumlahLain(); //Memanggil modul untuk membaca inputan nominal lain
	gotoxy(88,24);
	scanf("%d", &opsi);
	if (opsi == 5){
		if (strcmp(user[j].Status, "ENABLE")==0){
			if(user[j].Riwayat.nominal[user[j].Riwayat.k] % 50000 == 0 ){
				user[j].batas.limit_penarikan = user[j].batas.limit_penarikan + user[j].Riwayat.nominal[user[j].Riwayat.k];
				benar = validitasTransaksi(bhs, inputPin);
				if (benar == 1){
					user[j].total_saldo = user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k];
					system("cls");
					displayLoading(bhs);
					sleep(5);
					system("cls");
					displayTransaksiBerhasil(bhs);
					gotoxy(49,9);
					printf("SISA SALDO ANDA: %d",user[j].total_saldo);
					saldo_ATM = saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k];
					
					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
					user[j].Riwayat.transaksi[user[j].Riwayat.k] = 1;
					user[j].Riwayat.k = user[j].Riwayat.k + 1;	
						
					GO13:
					gotoxy(88, 24);
					konfirmasi = getch();
					switch(konfirmasi){
						case '5' : 
							MenuPenarikanCepat(bhs, inputPin);
							break;
						case '6' : 	
							system("cls");
							displayEnd(bhs);
							sleep(5);
							main();
						default:
							goto GO13;
					}
				}
			}
			else{
				system("cls");
				displayLoading(bhs);
				sleep(5);
				system("cls");
				displayGagalMin(bhs);
				GO20:
				gotoxy(88, 24);
				konfirmasi = getch();
				switch(konfirmasi){
					case '5' :
						MenuPenarikanCepat(bhs, inputPin);
						break;
					case '6' : 	
						system("cls");
						displayEnd(bhs);
						sleep(5);
						main();
					default:
						goto GO20;
				}	
			}
		}
		else if(strcmp(user[j].Status, "DISABLE")==0){
			system("cls");
			displayLoading(bhs); 
			sleep(5);
			system("cls");
			displayAkunDisable(bhs);
			DO5:
			gotoxy(88, 24);
			konfirmasi = getch();
			switch(konfirmasi){
				case '5' : 
					enableKartu(bhs, inputPin);
					break;
				case '6' : 	
					system("cls");
					displayEnd(bhs); //Memanggil modul displayEnd();
					sleep(5);
					MenuPenarikanCepat(bhs, inputPin);
				default:
					goto DO5;
			}
		}
	}
	else if (opsi == 6){
		goto BACK;
	}
	else {
		MenuPenarikanCepat(bhs, inputPin); //Memanggil modul menu penarikan cepat
	}
}

//Modul Validitas Transaksi
int validitasTransaksi(int bhs, char inputPin[7]){
	int isValid;
	char konfirmasi;
	
	if (user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k] >= 10000 && user[j].batas.limit_penarikan <= 10000000 && saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k]>0){
		isValid = 1;
	}
	else{
		if(user[j].total_saldo - user[j].Riwayat.nominal[user[j].Riwayat.k] < 10000){
			system("cls");
			displayLoading(bhs);
			sleep(5);
			system("cls");
			displayTransaksiGagal(bhs);
			GO:
			gotoxy(88, 24);
			konfirmasi = getch();
			switch(konfirmasi){
				case '5' : 
					MenuPenarikanCepat(bhs, inputPin);
					break;
				case '6' : 	
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto GO;
			}
		}
		if(user[j].batas.limit_penarikan > 10000000){
			system("cls");
			displayLoading(bhs);
			sleep(5);
			system("cls");
			displayTransaksiGagallimit(bhs);	
			GO2:
			gotoxy(88, 24);
			konfirmasi = getch();
			switch(konfirmasi){
				case '5' : 
					MenuPenarikanCepat(bhs, inputPin);
					break;
				case '6' : 	
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto GO2;
			}
		}
		if(saldo_ATM - user[j].Riwayat.nominal[user[j].Riwayat.k]<=0){
			system("cls");
			displayLoading(bhs);
			sleep(5);
			system("cls");
			displaySaldoAtmHabis(bhs);	
			GO3:
			gotoxy(88, 24);
			konfirmasi = getch();
			switch(konfirmasi){
				case '5' : 
					MenuPenarikanCepat(bhs, inputPin);
					break;
				case '6' : 	
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto GO3;
			}
		}
	}
	return isValid;
}

//Modul baca inputan nominal lain
void bacaJumlahLain(){	
	gotoxy(52, 10);
	scanf("%d", &user[j].Riwayat.nominal[user[j].Riwayat.k]);
}

//Modul Menu Lainnya
void MenuLainnya(int bhs, char inputPin[7]){
	int opsi;
	
	system("cls");
	displayMenuLainnya(bhs); //Memanggil modul display menu lainnya
	KEMBALI:
    	scanf("%d",&opsi);
   	switch(opsi){
    		case 1: 
			MenuTransfer(bhs,inputPin); //Memanggil modul menu untuk transfer
    			break;
    		case 2: 
			Menu_setor(bhs, inputPin); //Memanggil modul menu untuk setor tunai
    			break;
    		case 3: 
			MenuInformasiSaldo(bhs,inputPin); //Memanggil modul menu untuk melihat informasi saldo
    			break;
    		case 4: 
			MenuUbahPin(bhs,inputPin); //Memanggil modul menu untuk ubah pin
    			break;
    		case 5: 
			system("cls");
			displayLoading(bhs);
			sleep(5);
			LihatMutasi(bhs); //Memanggil modul menu untuk melihat mutasi rekening
    			break;
    		case 6: 
			enableKartu(bhs, inputPin);
			break; 
    		case 98: 
			MenuPenarikanCepat(bhs,inputPin); //Memanggil modul menu sebelumnya yaitu penarikan cepat
    			break;
    		case 99: 
			main();	
    			break;
    		default :
    			MenuLainnya(bhs,inputPin); //Memanggil modulnya sendiri jika default
    	}
}

// Modul Menu Transfer
void MenuTransfer(int bhs,  char inputPin[7]){
 	char konfirmasi;
	int benar = 0;
 	int Sama = 0;
 	char No_Rek[10];
    	int admin;
	int opsi;
    
	if (strcmp(user[j].Status, "ENABLE")==0){
		system("cls");
		displayMenuTransfer(bhs); //Memanggil modul untuk menampilkan display menu transfer
		Label1:
		gotoxy(55,7);
	 	scanf ("%s", No_Rek);
	 	if (strcmp(No_Rek, user[j].No_Rekening)==0){
	 		MenuTransfer(bhs, inputPin); 
		}
		Sama = cek_ValiditasNorek(bhs, No_Rek); //Memanggil modul untuk validasi No.Rekening tujuan
	
		if(Sama==1){
	 		gotoxy(90,24);
			scanf("%d",&opsi);
			switch(opsi){
				case 4 : 
					if (strcmp(user[j].Bank, user[r].Bank)==0){
	             				admin = 0;
					}
					else{
					 	admin = 3000;
					 }
			    	    	system("cls");
			        	displayProsesTransfer(bhs); //Memanggil modul untuk menampilkan display proses transfer
			    		gotoxy(56,8);
	             			scanf("%d", &user[j].Riwayat.nominal[user[j].Riwayat.k]);
					user[j].batas.limit_transfer = user[j].batas.limit_transfer + user[j].Riwayat.nominal[user[j].Riwayat.k]; //Assignment untuk batas limit transfer
					benar = cek_ValiditasTransfer(admin); //Memanggil modul untuk validasi Nominal Transfer
			        	if (benar==1){
	             				if (user[j].Riwayat.nominal[user[j].Riwayat.k]>=50000){
							user[j].total_saldo=user[j].total_saldo-user[j].Riwayat.nominal[user[j].Riwayat.k]-admin;
	             					system("cls");
	             					displaykonfirmasitrf(bhs, admin); //Memanggil modul untuk menampilkan display konfirmasi transfer
	             					konfirmasitrf(bhs,inputPin); //Memanggil modul untuk konfirmasi Transfer
	             					user[r].total_saldo = user[r].total_saldo + user[j].Riwayat.nominal[user[j].Riwayat.k];
	             					user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
	             					strncpy(user[j].Riwayat.NamaBank[user[j].Riwayat.k], user[r].Bank, 10);
							strncpy(user[j].Riwayat.NoRek[user[j].Riwayat.k], user[r].No_Rekening, 10);
							strncpy(user[j].Riwayat.NamaUser[user[j].Riwayat.k], user[r].Nama, 30);
							user[j].Riwayat.transaksi[user[j].Riwayat.k] = 2;
							user[j].Riwayat.k = user[j].Riwayat.k + 1;
								
	             					system("cls");
	             					displaygoodtransfer(bhs); //Memanggil modul untuk menampilkan transfer berhasil
	             					if (bhs == 1){
								gotoxy(50,15);
		             					printf("SISA SALDO ANDA : %d", user[j].total_saldo);
	             					}
	             					else if(bhs == 2){
	             						gotoxy(45,15);
		             					printf("YOUR REMAINING BALANCE : %d", user[j].total_saldo);
							}
	             					MenuKonfirmasi(bhs,inputPin);
								
							DO:
							gotoxy(88, 24);
							konfirmasi = getch();
							switch(konfirmasi){
								case '5' : 
									MenuLainnya(bhs,inputPin);
									break;
								case '6' : 	
									system("cls");
									displayEnd(bhs);
									sleep(5);
									main();
								default:
									goto DO;
	             					}
						}
						else{
							system("cls");
							displayLoading(bhs);
							sleep(5);
							system("cls");
							displayGagalMin(bhs);
							GO21:
							gotoxy(88, 24);
							konfirmasi = getch();
							switch(konfirmasi){
								case '5' : 
									MenuPenarikanCepat(bhs,inputPin);
									break;
								case '6' : 	
									system("cls");
									displayEnd(bhs);
									sleep(5);
									main();
								default:
									goto GO21;
							}	
						}	 
			    		}
					else {
						if(user[j].total_saldo-user[j].Riwayat.nominal[user[j].Riwayat.k]<10000){
				    			system("cls");
					    		displayLoading(bhs);
					    		sleep(5);
					    		system("cls");
					    		displaytransfergagal(bhs);
				    	
							DO2:
							gotoxy(88, 24);
							konfirmasi = getch();
							switch(konfirmasi){
								case '5' : 
									MenuLainnya(bhs,inputPin);
									break;
								case '6' : 	
									system("cls");
									displayEnd(bhs);
									sleep(5);
									main();
								default:
									goto DO2;
							}
						}	
						if(user[j].batas.limit_transfer>1000000){
							system("cls");
							displayLoading(bhs);
							sleep(5);
							system("cls");
							displayTransaksiGagallimit(bhs);
							DO3:
							gotoxy(88, 24);
							konfirmasi = getch();
							switch(konfirmasi){
								case '5' : 
									MenuLainnya(bhs, inputPin);
									break;
								case '6' : 	
									system("cls");
									displayEnd(bhs);
									sleep(5);
									main();
								default:
									goto DO3;
							}
						}
					}
		        		break;
				case 5 :  
				 	MenuTransfer(bhs,inputPin);
					break;
				default : 	        
	  				MenuTransfer(bhs,inputPin);
	  				break;
			}
	  	}
	 	else {
	 		system("cls");
			displayNo_RekNull(bhs);
			goto Label1;
	 	}
	}
	else if(strcmp(user[j].Status, "DISABLE")==0){
		system("cls");
		displayLoading(bhs); 
		sleep(5);
		system("cls");
		displayAkunDisable(bhs);
		DO6:
		gotoxy(88, 24);
		konfirmasi = getch();
		switch(konfirmasi){
			case '5' : 
				enableKartu(bhs, inputPin);
				break;
			case '6' : 	
				system("cls");
				displayEnd(bhs); //Memanggil modul displayEnd();
				sleep(5);
				MenuLainnya(bhs, inputPin);
			default:
				goto DO6;
		}
	}
}

//Modul cek validitas no.rekening
int cek_ValiditasNorek(int bhs, char No_Rek[10]){
	int betul;
	int b = 0;
	while (user[b].total_saldo != 0){
		while (b!= j){
			if(strcmp(No_Rek, user[b].No_Rekening)==0){
		     		betul=1;
		     	 	r= b;
		     		break;
		 	}
	    	else {
				betul=0;
				break;
			}
		}
		if (betul == 1){
			break;
		}
		b = b + 1;
	}
	return betul;
}
  
//Modul cek validitas nominal transfer
int cek_ValiditasTransfer(int admin){
    	int Betul;
	
	if(user[j].total_saldo-user[j].Riwayat.nominal[user[j].Riwayat.k]-admin>=10000&&user[j].batas.limit_transfer <=10000000){
     		Betul = 1;
    	}
   	else {
		Betul = 0;
	}
	return Betul;	
 }

//Modul Konfirmasi Transfer
void konfirmasitrf(int bhs,char inputPin[7]){
 	int opsi;
	gotoxy(90,24);
 	scanf("%d", &opsi);
 	switch (opsi){
 		case 5 : 
			system("cls");
           		displayLoading(bhs);
            		sleep(5);
             		system("cls");
             		displayTransaksiBerhasil(bhs);
             		break;
        	case 6 :    
			MenuTransfer(bhs,inputPin);
		default :
			konfirmasitrf(bhs,inputPin);	
	}
 }
 
 //Modul transaksi lainnya
 void MenuKonfirmasi(int bhs, char inputPin[7]){
 	int opsi;
 	gotoxy(90,24);
 	scanf("%d", &opsi);
 	switch (opsi){
 		case 5 : 
			system("cls");
             		MenuLainnya(bhs,inputPin);
           		break;
  	  	case 6:  
			system("cls");
			displayEnd(bhs);
			sleep(5);
			main();
        		break;
		default : 
			MenuKonfirmasi(bhs,inputPin);		
 	}
}

//Modul Setor Tunai
void Menu_setor(int bhs, char inputPin[7]){
	int benar = 0;
	char konfirmasi;
	if (strcmp(user[j].Status, "ENABLE")==0){
		system("cls");
		displayMenuSetor(bhs);
		gotoxy(54,13);
		scanf("%d", &user[j].Riwayat.nominal[user[j].Riwayat.k]);
		benar = cekvalid_setor();
		if(benar==1){
			user[j].total_saldo = user[j].total_saldo + user[j].Riwayat.nominal[user[j].Riwayat.k];
			system("cls");
			displayLoading(bhs);
			sleep(5);
			system("cls");
			displaysetorberhasil(bhs);
			saldo_ATM = saldo_ATM + user[j].Riwayat.nominal[user[j].Riwayat.k];
			user[j].Riwayat.sizeTransaksi = user[j].Riwayat.sizeTransaksi + 1;
			user[j].Riwayat.transaksi[user[j].Riwayat.k] = 3;
			user[j].Riwayat.k = user[j].Riwayat.k + 1;
			
			gotoxy(60,13);
			printf("%d", user[j].total_saldo);
			bacasetorlagi(bhs,inputPin);	
		}
		else {
			if (user[j].Riwayat.nominal[user[j].Riwayat.k]%50000!=0){
			 	Menu_setor(bhs, inputPin);
			}
			if (user[j].batas.limit_setor>5000000){
				system("cls");
				displayLoading(bhs);
				sleep(5);
				system("cls");
				displayTransaksiGagallimit(bhs);
				bacasetorlagi(bhs,inputPin);
			}
			 
		}
	}
	else if(strcmp(user[j].Status, "DISABLE")==0){
		system("cls");
		displayLoading(bhs); 
		sleep(5);
		system("cls");
		displayAkunDisable(bhs);
		DO7:
		gotoxy(88, 24);
		konfirmasi = getch();
		switch(konfirmasi){
			case '5' : 
				enableKartu(bhs, inputPin);
				break;
			case '6' : 	
				system("cls");
				displayEnd(bhs); //Memanggil modul displayEnd();
				sleep(5);
				MenuLainnya(bhs,inputPin);
			default:
				goto DO7;
		}
	}
}

//Modul cek validitas nominal setor
int cekvalid_setor(){
	int betul;
	user[j].batas.limit_setor = user[j].batas.limit_setor + user[j].Riwayat.nominal[user[j].Riwayat.k];
	if(user[j].Riwayat.nominal[user[j].Riwayat.k] % 50000 == 0 && user[j].batas.limit_setor <= 5000000){
		betul=1;
 	}
 	else {
		betul=0;
		}
	return betul;
}

//Modul setor lagi
void bacasetorlagi(int bhs,char inputPin[7]){
	int opsi;
	gotoxy(92,24);
	scanf("%d", &opsi);
	switch (opsi){
		case 5 : 
		       MenuLainnya(bhs,inputPin);
		       break;
		case 6 : 
			system("cls");
			displayEnd(bhs);
			sleep(5);
			main();
	    		break;
	    default:
			bacasetorlagi(bhs,inputPin);
	}
}

//Modul Informasi Saldo
void MenuInformasiSaldo(int bhs,  char inputPin[7]){
	int opsi;
	system("color 1F");
	system("cls");
	displayLoading(bhs);
	sleep(5);
	system("cls");
	displayInformasiSaldo(bhs);
	scanf("%d", &opsi);
	switch (opsi){
		case 5: 
			MenuLainnya(bhs,inputPin);
			break;
		case 6: 
			system("cls");
			displayEnd(bhs);
			sleep(5);
			main();
			break;
		default : 
			MenuInformasiSaldo(bhs,inputPin);
	}
}

//Modul Ubah Pin
void MenuUbahPin(int bhs, char inputPin[7]){
	char konfirmasi;
	if (strcmp(user[j].Status, "ENABLE")==0){
		InputPinLama(bhs,inputPin); //Memanggil modul UbahPinLama();
	}
	else if(strcmp(user[j].Status, "DISABLE")==0){
		system("cls");
		displayLoading(bhs); 
		sleep(5);
		system("cls");
		displayAkunDisable(bhs);
		DO8:
		gotoxy(88, 24);
		konfirmasi = getch();
		switch(konfirmasi){
			case '5' : 
				enableKartu(bhs, inputPin);
				break;
			case '6' : 	
				system("cls");
				displayEnd(bhs); //Memanggil modul displayEnd();
				sleep(5);
				MenuLainnya(bhs, inputPin);
			default:
				goto DO8;
		}
	}
}

void InputPinLama(int bhs, char inputPin[7]){
	int i = 1;
	int benar = 0;
	system("cls");
	displayUbahPinLama(bhs);
	while(benar == 0 && i<=3){
		bacaPin(inputPin);
		benar = Cek_validitas(inputPin, bhs, &i);
	}
	if (benar == 1){
		MasukkanPinBaru(bhs,inputPin);
	}
}

void MasukkanPinBaru(int bhs, char inputPin[7]){
	int i;
	int benar = 0;
	char inputPinBaru[7];
	char konfirmasiPin[7];
	int opsi;
	
	system("cls");
	displayPinBaru(bhs);
	gotoxy(53, 11);
    	for(int i = 0; i < 6; i++){
        	inputPinBaru[i] = _getch();
        	putchar('*');
        	putchar(' ');
    	}
    	i = 1;
    	system("cls");
	displaykonfirmasiPin(bhs);
	while(benar == 0 && i<=3){
		bacaKonfirmasiPinBaru(konfirmasiPin, bhs); //Modul untuk baca konfirmasi pin baru
		benar = Cek_validitasPinBaru(inputPinBaru, konfirmasiPin, &i, bhs,inputPin); //Modul untuk mengonfirmasi pin baru
	}
	if (benar == 1){
		PINBERHASIL:
		system("cls");
		displayLoading(bhs);
		sleep(5);
		system("cls");
		if (strcmp(user[j].Status, "ENABLE")==0){
			displayUbahPinBerhasil(bhs);
			scanf("%d", &opsi);
			switch (opsi){
				case 5: 
					system("cls");
					MenuLainnya(bhs,inputPin);	
					break;
				case 6: 
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto PINBERHASIL;
			}
		}
		else if(strcmp(user[j].Status, "DISABLE")==0){
			Label6:
			system("cls");
			displayEnableBerhasil(bhs);
			strcpy(user[j].Status, "ENABLE");
			scanf("%d", &opsi);
			switch (opsi){
				case 5: 
					system("cls");
					MenuPenarikanCepat(bhs, inputPin);	
					break;
				case 6: 
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto Label6;
			}
		}
	}
}

//Modul Baca konfirmasi pin baru
void bacaKonfirmasiPinBaru(char konfirmasiPin[7], int bhs){
	system("cls");
	displaykonfirmasiPin(bhs);
	gotoxy(53, 11);
    	for(int i = 0; i < 6; i++){
        	konfirmasiPin[i] = _getch();
		putchar('*');
		putchar(' ');
    	}
}
//Modul validasi pin baru
int Cek_validitasPinBaru(char inputPinBaru[7], char konfirmasiPin[7], int *i, int bhs, char inputPin[7]){
	int benar;
	int opsi;
	if(strcmp(inputPinBaru,konfirmasiPin)==0){
		strcpy(user[j].Pin, inputPinBaru);
		strcpy(inputPin, inputPinBaru);
    		benar=1;
	}
	else if(*i<3){
		benar = 0;
		i = i + 1;
		system("cls");
		displaySalahMengubahPin(bhs);
	}
	else{
		PINGAGALBARU:
		system("cls");
		displayUbahPinGagal(bhs);
		scanf("%d", &opsi);
		switch (opsi){
			case 5: 
				MenuLainnya(bhs,inputPin);
				break;
			case 6: 
				system("cls");
				displayEnd(bhs);
				sleep(5);
				main();
			default:
				goto PINGAGALBARU;
		}
	}
	return benar;
}

//Modul untuk menampilkan mutasi rekening
void LihatMutasi(int bhs){
	int i;
	system("cls");
	if(user[j].Riwayat.sizeTransaksi > 0){
		if (bhs == 1){
			printf("\n|--------------------------|");
			printf("\n| Daftar Mutasi		   |");
			printf("\n|--------------------------|");
			printf("\n|biaya transaksi : Rp. %d|", 1000);
			user[j].total_saldo = user[j].total_saldo - 1000;
		}
		else if(bhs == 2){
			printf("\n|--------------------------|");
			printf("\n| Mutation List		   |");
			printf("\n|--------------------------|");
		}
		for(i=user[j].Riwayat.sizeTransaksi-1; i>=user[j].Riwayat.sizeTransaksi-5; i--){
			cetakMutasi(bhs, &i);
		}
		printf("\n|--------------------------|");
	}else{
		printf("\nTidak ada Transaksi yang dilakukan\n");
	}
	sleep(5);
	main();
}

void enableKartu(int bhs,char inputPin[7]){
	int hari, bulan, tahun;
	int benar;
	int i;
	int opsi;
	
	if (strcmp(user[j].Status, "ENABLE")==0){
		system("cls");
		displayEnable(bhs);
		Label5:
		scanf("%d", &opsi);
			switch (opsi){
				case 5: 
					system("cls");
					MenuPenarikanCepat(bhs, inputPin);	
					break;
				case 6: 
					system("cls");
					displayEnd(bhs);
					sleep(5);
					main();
				default:
					goto Label5;
			}
	}
	else if(strcmp(user[j].Status, "DISABLE")==0){
		i = 1;
		benar = 0;
		system("cls");
		displayEnableTanggalLahir(bhs);
		while (benar == 0 && i <=3){
			gotoxy(53,11);
			scanf ("%d %d %d", &hari, &bulan, &tahun);
			benar = validasi_TanggalLahir(hari, bulan, tahun, &i, bhs, inputPin);
		}
		if (benar == 1){
			InputPinLama(bhs, inputPin);
		}
	}
}

int validasi_TanggalLahir(int hari, int bulan, int tahun, int *i, int bhs, char inputPin[7]){
	int betul;
	int opsi;
	if (hari == user[j].Tanggal_Lahir.day && bulan == user[j].Tanggal_Lahir.month && tahun == user[j].Tanggal_Lahir.years){
		betul = 1;
	}
	else if (*i < 3){
		betul = 0;
		*i = *i + 1;
		system("cls");
		displayEnableTanggalLahirSalah3x(bhs);
	}
	else{
		system("cls");
		displayLoading(bhs);
		sleep(5);
		system("cls");
		displayEnableGagal(bhs);
		Label3:
		scanf("%d", &opsi);
		switch (opsi){
			case 5: 
				system("cls");
				MenuPenarikanCepat(bhs, inputPin);	
				break;
			case 6: 
				system("cls");
				displayEnd(bhs);
				sleep(5);
				main();
			default:
				goto Label3;
		}
	}
	return betul;
}

//Prosedur Display

void gotoxy(int x, int y){
    	COORD coord;
	coord.X = x;
    	coord.Y = y;
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void printToxy(int x, int y, char* label){
    	gotoxy(x,y);
    	printf("%s",label);
}

void header(){
	for (int i = 1; i<25; i++){
    		printToxy(15,1+i,"||");
	}
	for (int i =0; i<=119; i++){
    		printToxy(0+i,1,"=");
	}
	for (int i = 1; i<25; i++){
    		printToxy(100,1+i,"||");
	}
	for (int i =0; i<=119; i++){
    		printToxy(0+i,25,"=");
	}
}

void displayLoginAtm(){
	int i;
	header();
	printToxy(42,4,"SILAKAN LOG IN/BUAT AKUN ATM ANDA");
	printToxy(40,3,"PLEASE LOG IN/CREATE YOUR ATM ACCOUNT");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");


	printToxy(90,9,"LOG IN");
	printToxy(90,13,"REGISTER");
	printToxy(60,24,"\t Masukan pilihan anda : ");
}

void displayBacaKartu(){
	int i;
	header();
	printToxy(50,3,"SILAKAN MASUKKAN");
	printToxy(51,4,"KARTU ATM ANDA");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	for(i=1; i<35;i++){
		printToxy(20+i,9,"_");
	}
	for(i=1; i<10;i++){
		printToxy(20,9+i,"|");
	}
	for(i=1; i<35;i++){
		printToxy(20+i,18,"_");
	}
	for(i=1; i<16;i++){
		printToxy(55,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,6,"_");
	}
	for(i=1; i<16;i++){
		printToxy(58,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,21,"_");
	}
	printToxy(24,10,"_______");
	printToxy(24,12,"_______");
	printToxy(23,11,"|");
	printToxy(23,12,"|");
	printToxy(31,12,"|");
	printToxy(31,11,"|");
	printToxy(60,9,"MASUKKAN NO REKENING ANDA UNTUK");	
	printToxy(60,10,"VALIDASI KARTU : ");		
}

void displayTidakTerdaftar(){
	int i;
	header();
	printToxy(38,3,"REKENING YANG ANDA MASUKKAN TIDAK TERDAFTAR");
	printToxy(39,4,"SILAKAN MEMASUKKAN KEMBALI NOMOR REKENING");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	for(i=1; i<35;i++){
		printToxy(20+i,9,"_");
	}
	for(i=1; i<10;i++){
		printToxy(20,9+i,"|");
	}
	for(i=1; i<35;i++){
		printToxy(20+i,18,"_");
	}
	for(i=1; i<16;i++){
		printToxy(55,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,6,"_");
	}
	for(i=1; i<16;i++){
		printToxy(58,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,21,"_");
	}	
	printToxy(24,10,"_______");
	printToxy(24,12,"_______");
	printToxy(23,11,"|");
	printToxy(23,12,"|");
	printToxy(31,12,"|");
	printToxy(31,11,"|");	
	printToxy(60,9,"MASUKKAN NO REKENING ANDA : ");	
}

void displaybuatakun(){
	int i;
	header();
	printToxy(50,3,"SILAKAN MASUKKAN");
	printToxy(51,4,"KARTU ATM ANDA");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	for(i=1; i<35;i++){
		printToxy(20+i,9,"_");
	}
	for(i=1; i<10;i++){
		printToxy(20,9+i,"|");
	}
	for(i=1; i<35;i++){
		printToxy(20+i,18,"_");
	}
	for(i=1; i<16;i++){
		printToxy(55,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,6,"_");
	}
	for(i=1; i<16;i++){
		printToxy(58,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,21,"_");
	}
	printToxy(24,10,"_______");
	printToxy(24,12,"_______");
	printToxy(23,11,"|");
	printToxy(23,12,"|");
	printToxy(31,12,"|");
	printToxy(31,11,"|");	
}

void displayAkunBerhasil(){
	int i;
	header();
	printToxy(50,3,"KARTU ATM TELAH");
	printToxy(48,4,"BERHASIL DIDAFTARKAN");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	for(i=1; i<35;i++){
		printToxy(20+i,9,"_");
	}
	for(i=1; i<10;i++){
		printToxy(20,9+i,"|");
	}
	for(i=1; i<35;i++){
		printToxy(20+i,18,"_");
	}
	for(i=1; i<16;i++){
		printToxy(55,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,6,"_");
	}
	for(i=1; i<16;i++){
		printToxy(58,6+i,"|");
	}
	for(i=1; i<3;i++){
		printToxy(55+i,21,"_");
	}
	printToxy(24,10,"_______");
	printToxy(24,12,"_______");
	printToxy(23,11,"|");
	printToxy(23,12,"|");
	printToxy(31,12,"|");
	printToxy(31,11,"|");			
}

void displayMenuBahasa(){
	header();
	printToxy(50,3,"PEMILIHAN BAHASA");
	printToxy(48,4,"LANGUAGE REFFFERENCE");
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(82,9,"BAHASA INDONESIA");
	printToxy(105,13,"<= [5]");
	printToxy(82,13,"ENGLISH LANGUAGE");
	printToxy(105,17,"<= [6]");
	printToxy(60,24,"\t Masukan pilihan anda : ");
}

void displayMenuPinId(int bhs){
	header();
	if (bhs == 1){
		printToxy(53,3,"MASUKKAN PIN");
		printToxy(54,4,"ATM ANDA !");
	}
	else if(bhs == 2){
		printToxy(53,3,"ENTER YOUR");
		printToxy(54,4,"ATM PIN !");
	}
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(53,14,"_ _ _ _ _ _");
	printToxy(105,17,"<= [6]");
}

void displaySalahPin(int bhs){
	header();
	printToxy(43,6,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(53,14,"_ _ _ _ _ _");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(105,21,"<=[99]");
	if(bhs == 1){
		printToxy(52,3,"PIN ANDA SALAH ");
		printToxy(47,4,"SILAKAN MASUKKAN KEMBALI ");
		printToxy(49,5,"NOMOR PIN YANG BENAR ");
		printToxy(47,16,"KARTU ANDA AKAN DIBLOKIR");
		printToxy(43,17,"BILA ANDA SALAH PIN 3(TIGA) KALI");
		printToxy(90,21,"KELUAR");
		
		
	}
	else if(bhs == 2){
		printToxy(52,3,"YOUR PIN IS WRONG ");
		printToxy(53,4,"PLEASE RE-ENTER ");
		printToxy(49,5,"THE CORRECT PIN NUMBER ");
		printToxy(47,16,"YOU CARD WILL BE BLOCKED");
		printToxy(43,17,"IF YOU WRONG PIN 3(THREE) TIMES");
	}
}

void displayAkunTerblokir(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(46,13,". . . . . . . . . . . . . . ");
	if (bhs == 1){
		printToxy(48,3,"ANDA TELAH 3 KALI SALAH");
		printToxy(52,4,"MEMASUKKAN PIN");
		printToxy(47,17,"SILAHKAN AMBIL KARTU ANDA");
		printToxy(46,18,"DAN HUBUNGI CALL CENTER KAMI");
		printToxy(50,11,"KARTU ANDA SEMENTARA");
		printToxy(48,12,"TIDAK DAPAT DIPERGUNAKAN");
	}
	else if(bhs == 2){
		printToxy(48,3,"YOU HAVE ENTERED THE WRONG");
		printToxy(55,4,"PIN 3 TIMES");
		printToxy(50,17,"PLEASE TAKE YOUR CARD");
		printToxy(46,18,"AND CONTACT OUR CALL CENTER");
		printToxy(55,11,"YOU CARD IS");
		printToxy(50,12,"TEMPORARILY UNUSABLE");
	}
}

void displayMenuPenarikanCepat(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(18,9,"Rp. 250.000,00");
	printToxy(7,13,"[2] =>");
	printToxy(18,13,"Rp. 500.000,00");
	printToxy(7,17,"[3] =>");
	printToxy(18,17,"Rp. 1.000.000,00");
	printToxy(105,9,"<= [4]");
	printToxy(83,9,"Rp. 1.250.000,00");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(105,21,"<=[99]");
	if (bhs == 1){
		printToxy(50,3,"MENU PENARIKAN CEPAT");
		printToxy(44,4,"SILAHKAN PILIH JUMLAH PENARIKAN");
		printToxy(83,13,"Jumlah Lain");
		printToxy(83,17,"Menu Lainnya");
		printToxy(90,21,"KELUAR");
		printToxy(60,24,"\t Masukan pilihan anda : ");
		
	}
	if (bhs == 2){
		printToxy(50,3,"QUICK WITHDRAWAL MENU");
		printToxy(42,4,"PLEASE SELECT THE WITHDRAWAL AMOUNT");
		printToxy(83,13,"Another Amount");
		printToxy(83,17,"Other Menus");
		printToxy(90,21,"EXIT");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayTransaksiBerhasil(int bhs){
	header();
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if(bhs == 1){
		printToxy(52,3,"DETAIL TRANSAKSI");
		printToxy(95,13,"YA");
		printToxy(92,17,"TIDAK");
		printToxy(51,7,"TRANSAKSI BERHASIL");
		gotoxy(49,9);
		printf("SISA SALDO ANDA: %d", user[j].total_saldo);
		printToxy(40,11,"APAKAH ANDA INGIN MELANJUTKAN TRANSAKSI ?");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs ==2){
		printToxy(52,3,"TRANSACTION DETAILS");
		printToxy(95,13,"YES");
		printToxy(95,17,"NO");
		printToxy(51,7,"SUCCESSFUL TRANSACTION");
		gotoxy(49,9);
		printf("YOUR CURRENT BALANCE: %d", user[j].total_saldo);
		printToxy(40,11,"DO YOU WANT TO CONTINUE THE TRANSACTION ?");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayTransaksiGagal(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if(bhs == 1){
		printToxy(52,3,"DETAIL TRANSAKSI");
		printToxy(95,13,"YA");
		printToxy(92,17,"TIDAK");
		printToxy(52,8,"TRANSAKSI GAGAL");
		printToxy(48,9,"PASTIKAN SALDO ANDA CUKUP");
		printToxy(40,11,"APAKAH ANDA INGIN MELANJUTKAN TRANSAKSI ?");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(52,3,"TRANSACTION DETAILS");
		printToxy(95,13,"YES");
		printToxy(95,17,"NO");
		printToxy(52,8,"TRANSACTION FAILED");
		printToxy(45,9,"MAKE SURE YOUR BALANCE IS ENOUGH");
		printToxy(40,11,"DO YOU WANT TO CONTINUE THE TRANSACTION ?");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayTransaksiGagallimit(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"DETAIL TRANSAKSI");
		printToxy(95,13,"YA");
		printToxy(92,17,"TIDAK");
		printToxy(53,8,"TRANSAKSI GAGAL");
		printToxy(42,9,"ANDA TELAH MELEWATI LIMIT BATAS PENARIKAN");
		printToxy(42,11,"APAKAH ANDA INGIN MELANJUTKAN TRANSAKSI ?");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(50,3,"TRANSACTION DETAILS");
		printToxy(95,13,"YES");
		printToxy(95,17,"NO");
		printToxy(52,8,"TRANSACTION FAILED");
		printToxy(42,9,"YOU HAVE EXCEEDED THE WITHDRAWAL LIMIT");
		printToxy(40,11,"DO YOU WANT TO CONTINUE THE TRANSACTION ?");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayMenuJumlahLain(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(48,10,"Rp.");
	if (bhs == 1){
		printToxy(51,3,"SILAHKAN MASUKKAN");
		printToxy(47,4,"JUMLAH YANG INGIN DI TARIK ");
		printToxy(19, 17,"BATAL");
		printToxy(92,17,"SALAH");
		printToxy(92,13,"BENAR");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(54,3,"PLEASE ENTER");
		printToxy(44,4,"THE AMOUNT YOU WISH TO WITHDRAWL ");
		printToxy(19, 17,"CANCEL");
		printToxy(92,17,"FALSE");
		printToxy(92,13,"TRUE");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayEnd(int bhs){
  	header();
  	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
  	if (bhs == 1){
		printToxy(55,3,"BANK RAKYAT");
		printToxy(44,10,"TERIMA KASIH TELAH MEMERCAYAI KAMI");
		printToxy(43,11,"SEBAGAI PARTNER ANDA DALAM PERBANKAN ");
	}
	else if (bhs == 2){
		printToxy(55,3,"BANK RAKYAT");
		printToxy(47,10,"THANK YOU FOR TRUSTING US AS ");
		printToxy(49,11,"YOUR PARTNER IN BANKING ");
	}
}

void displayMenuLainnya(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(7,21,"[98]=>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(105,21,"<=[99]");
		
	if (bhs == 1){
		printToxy(48,3,"SILAKAN PILIH TRANSAKSI");
		printToxy(51,4,"YANG ANDA INGINKAN");
		printToxy(18,9,"TRANSFER");
		printToxy(18,13,"SETOR TUNAI");
		printToxy(18,17,"INFORMASI SALDO");
		printToxy(84,9,"UBAH PIN");
		printToxy(84,13,"MUTASI REKENING");
		printToxy(84,17,"ENABLE KARTU");
		printToxy(84,21,"KELUAR");
		printToxy(18,21,"MENU SEBELUMNYA");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	
	}
	else if (bhs == 2){
		printToxy(49,3,"SELECT THE TRANSACTION");
		printToxy(56,4,"YOU WANT");
		printToxy(18,9,"TRANSFER");
		printToxy(18,13,"CASH DEPOSIT");
		printToxy(18,17,"BALANCE INFORMATION");
		printToxy(84,9,"CHANGE PIN");
		printToxy(84,13,"ACCOUNT MUTATION");
		printToxy(84,17,"ENABLE CARD");
		printToxy(90,21,"EXIT");
		printToxy(18,21,"PREVIOUS MENUS");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displayMenuTransfer(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(49,8,"_ _ _ _ _ _ _ _ _ _ _");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(90,9,"BENAR");
		printToxy(44,3,"MASUKKAN NOMOR REKENING TUJUAN");
		printToxy(90,13,"SALAH");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(42,3,"ENTER THE DESTINATION ACCOUNT NUMBER");
		printToxy(90,9,"TRUE");
		printToxy(90,13,"FALSE");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

 void displayNo_RekNull(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(49,8,"_ _ _ _ _ _ _ _ _ _ _");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(90,9,"BENAR");
		printToxy(48,3,"NOMOR REKENING TIDAK ADA");
		printToxy(44,4,"MASUKKAN NO REKENING YANG BENAR");
		printToxy(90,13,"SALAH");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(47,3,"NUMBER ACCOUNT DOESN'T EXIST");
		printToxy(42,4,"ENTER THE DESTINATION ACCOUNT NUMBER");
		printToxy(90,9,"TRUE");
		printToxy(90,13,"FALSE");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

 void displayProsesTransfer(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(52,8,"RP. ");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(48,3,"MASUKKAN JUMLAH NOMINAL");
		printToxy(49,4,"YANG AKAN DITRANSFER ");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if (bhs == 2){
		printToxy(48,3,"ENTER THE NOMINAL AMOUNT");
		printToxy(51,4,"TO BE TRANSFERED ");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
}

void displaytransfergagal(int bhs){
	header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(51,3,"MAAF TRANSFER GAGAL");
		printToxy(48,4,"SALDO ANDA TIDAK MENCUKUPI ");
		printToxy(50,13,"PASTIKAN SALDO ANDA CUKUP ");
		printToxy(90,13,"LANJUTKAN");
		printToxy(90,17,"EXIT");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if (bhs == 2){
		printToxy(51,3,"SORRY TRANSFER FAILED");
		printToxy(37,4,"YOUR ACCOUNT NUMBER/BALANCE IS WRONG/INNADEQUATE ");
		printToxy(45,13,"MAKE SURE YOUR BALANCE IS ENOUGH ");
		printToxy(90,13,"CONTINUE");
		printToxy(90,17,"EXIT");                                               
		printToxy(60,24,"\t Enter Your Choice : ");  
	}
}

void displaygoodtransfer(int bhs){
   	header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(50,3,"TRANSAKSI TELAH SELESAI");
		printToxy(49,4,"PERLU TRANSAKSI YANG LAIN ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda : ");
	}
	else if(bhs == 2){
		printToxy(47,3,"TRANSACTION HAS BEEN COMPLETED");
		printToxy(49,4,"NEED ANOTHER TRANSACTION ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"\t Enter Your Choice : ");
	}
 }

void displaykonfirmasitrf(int bhs,int admin){
 	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"KONFIRMASI TRANSFER");
		printToxy(95,13,"YA");
		printToxy(92,17,"TIDAK");
		printToxy(50,9,"BANK       :");
	 	printf ("%s", user[r].Bank);
		printToxy(50,10,"TUJUAN     :");
		printf ("%s", user[r].No_Rekening);
		printToxy(50,11,"NAMA       :");
		printf ("%s", user[r].Nama);
		printToxy(50,12,"JUMLAH     :");
		printf ("%d", user[j].Riwayat.nominal[user[j].Riwayat.k]);
		printToxy(50,13,"ADMIN BANK :");
		printf ("%d", admin);
		printToxy(50,14,"TOTAL      :");
		printf ("%d", user[j].Riwayat.nominal[user[j].Riwayat.k]+admin);
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if (bhs == 2){
		printToxy(52,3,"TRANSFER CONFIRMATION");
		printToxy(95,13,"YES");
		printToxy(95,17,"NO");
		printToxy(50,9,"BANK       :");
	 	printf ("%s", user[r].Bank);
		printToxy(50,10,"DESTINATION:");
		printf ("%s", user[r].No_Rekening);
		printToxy(50,11,"NAME       :");
		printf ("%s", user[r].Nama);
		printToxy(50,12,"AMOUNT     :");
		printf ("%d", user[j].Riwayat.nominal[user[j].Riwayat.k]);
		printToxy(50,13,"ADMIN FEE  :");
		printf ("%d", admin);
		printToxy(50,14,"TOTAL      :");
		printf ("%d", user[j].Riwayat.nominal[user[j].Riwayat.k]+admin);
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
 }
 
 void displaysetorberhasil(int bhs){
    header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(53,3,"PENYETORAN BERHASIL ");
		printToxy(34,13,"SALDO ANDA SAAT INI : ");
		printToxy(53,17,"SETOR LAGI ?");
		printToxy(94,13,"YA");
		printToxy(94,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if (bhs == 2){
		printToxy(53,3,"SUCCESSFUL DEPOSIT ");
		printToxy(34,13,"YOUR CURRENT BALANCE : ");
		printToxy(53,17,"DEPOSIT AGAIN ?");
		printToxy(94,13,"YES");
		printToxy(94,17,"NO");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
	
}

 void displayLoading(int bhs){
	header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"HARAP TUNGGU PROSES ");
		printToxy(48,4,"TRANSAKSI SEDANG BERLANGSUNG  ");
		printToxy(40,13,"TERIMA KASIH TELAH BERTRANSAKSI DENGAN KAMI");
	}
	else if (bhs ==2){
		printToxy(52,3,"PLEASE WAIT FOR THE ");
		printToxy(45,4,"TRANSACTION PROCESS TO TAKE PLACE  ");
		printToxy(45,13,"THANK YOU FOR TRANSACTING WITH US");
	}
}

void displayInformasiSaldo(int bhs){
	header();
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(52,9,"RP. ");
	printf("%d", user[j].total_saldo);
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(49,4,"SALDO REKENING ANDA");
		printToxy(92,13,"IYA");
		printToxy(92,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if (bhs == 2){
		printToxy(49,4,"YOUR ACCOUNT BALANCE");
		printToxy(92,13,"YES");
		printToxy(92,17,"NO");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
}

void displayUbahPinLama(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(53,14,"_ _ _ _ _ _");
	if (bhs == 1){
		printToxy(52,3,"PERUBAHAN PIN");
		printToxy(51,8,"MASUKKAN 6 DIGIT");
		printToxy(52,9,"PIN LAMA ANDA");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if(bhs == 2){
		printToxy(54,3,"PIN CHANGE");
		printToxy(52,8,"ENTER YOUR OLD");
		printToxy(53,9,"6 DIGIT PIN");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
}

void displayPinBaru(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(53,12,"_ _ _ _ _ _");
	if (bhs == 1){
		printToxy(52,3,"PERUBAHAN PIN");
		printToxy(51,8,"MASUKKAN 6 DIGIT");
		printToxy(52,9,"PIN BARU ANDA");
	}
	else if (bhs == 2){
		printToxy(54,3,"PIN CHANGE");
		printToxy(52,8,"ENTER YOUR NEW");
		printToxy(53,9,"6 DIGIT PIN");
	}
}

void displayUbahPinBerhasil(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"PERUBAHAN PIN");
		printToxy(52,12,"TRANSAKSI LAGI ?");
		printToxy(51,8,"UBAH PIN BERHASIL");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if (bhs == 2){
		printToxy(54,3,"PIN CHANGE");
		printToxy(50,12,"ANOTHER TRANSACTION ?");
		printToxy(48,8,"CHANGE PIN WAS SUCCESSFUL");
		printToxy(88,13,"YES");
		printToxy(88,17,"NO");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
}

void displayUbahPinGagal(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"PERUBAHAN PIN");
		printToxy(48,8,"ANDA TELAH 3(KALI) SALAH");
		printToxy(52,9,"MEMASUKKAN PIN");
		printToxy(51,6,"GAGAL MENGUBAH PIN");
		printToxy(50,11,"LANJUTKAN TRANSAKSI ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if(bhs == 2){
		printToxy(54,3,"PIN CHANGE");
		printToxy(46,8,"YOU HAVE CHANGED THE WRONG");
		printToxy(50,9,"PIN 3(THREE) TIMES");
		printToxy(49,6,"FAILED TO CHANGE PIN");
		printToxy(48,11,"CONTINUE TRANSACTION ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
}

void displaySalahMengubahPin(int bhs){
	header();
	printToxy(43,6,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(53,12,"_ _ _ _ _ _");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(52,3,"PIN ANDA SALAH ");
		printToxy(47,4,"SILAKAN MASUKKAN KEMBALI ");
		printToxy(49,5,"NOMOR PIN YANG BENAR ");
		printToxy(47,16,"ANDA AKAN DIKELUARKAN");
		printToxy(43,17,"BILA ANDA SALAH PIN 3(TIGA) KALI");
	}
	else if (bhs == 2){
		printToxy(52,3,"YOUR PIN IS WRONG ");
		printToxy(47,4,"PLEASE RE-ENTER THE ");
		printToxy(49,5,"CORRECT PIN NUMBER ");
		printToxy(47,16,"YOU WILL BE KICKED OUT");
		printToxy(43,17,"IF YOU WRONG PIN 3 TIMES");
	}
}

void displaykonfirmasiPin(int bhs){
	header();
	printToxy(43,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	printToxy(53,12,"_ _ _ _ _ _");
	if (bhs == 1){
		printToxy(47,3,"KONFIRMASI PERUBAHAN PIN");
		printToxy(51,8,"MASUKKAN KEMBALI");
		printToxy(52,9,"PIN BARU ANDA");
	}
	else if (bhs == 2){
		printToxy(52,3,"CONFIRM PIN CHANGE");
		printToxy(55,8,"RE-ENTER");
		printToxy(53,9,"YOUR NEW PIN");
	}
}

void displayMenuSetor(int bhs){
  	header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(50,3,"SILAKAN MASUKAN JUMLAH ");
		printToxy(49,4,"NOMINAL YANG AKAN DISETOR");
		printToxy(37,7,"HARAP MASUKKAN NOMINAL DENGAN KELIPATAN Rp. 50000");
		printToxy(34,13,"NOMINAL SETOR : Rp. ");
	}
	else if (bhs == 2){
		printToxy(50,3,"PLEASE ENTER THE NOMINAL ");
		printToxy(51,4,"AMOUNT TO BE DEPOSITED");
		printToxy(42,7,"PLEASE ENTER IN MULTIPLIES Rp. 50000");
		printToxy(34,13,"DEPOSIT AMOUNT : Rp. ");
	}
}

void displayGagalMin(int bhs){
  	header();
	printToxy(45,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(47,7,"MOHON MAAF TRANSAKSI GAGAL ");
		printToxy(38,8,"HARAP MASUKKAN JUMLAH NOMINAL MINIMUM Rp. 50000");
		printToxy(53,4,"DETAIL TRANSAKSI ");
		printToxy(44,12,"APAKAH ANDA INGIN TRANSAKSI LAGI?");
		printToxy(90,13,"YA");
		printToxy(87,17,"TIDAK");
		printToxy(60,24,"\t Masukan pilihan anda :  ");
	}
	else if (bhs == 2){
		printToxy(48,7,"SORRY TRANSACTION FAILED ");
		printToxy(36,8,"PLEASE ENTER THE MINIMUM NOMINAL AMOUNT OF Rp. 50000");
		printToxy(53,4,"TRANSACTION DETAIL ");
		printToxy(45,12,"DO YOU WANT ANOTHER TRANSACTION?");
		printToxy(92,13,"YES");
		printToxy(92,17,"NO");
		printToxy(60,24,"\t Enter Your Choice :  ");
	}
}

void cetakMutasi(int bhs, int *i){
	if (bhs == 1){
		if (user[j].Riwayat.transaksi[*i] == 1){
			printf("\n|			   |");
			printf("\n|	Penarikan	   |");
			printf("\n|	-Rp. %d	   |", user[j].Riwayat.nominal[*i]);
		}
		else if (user[j].Riwayat.transaksi[*i] == 2){
			printf("\n|			   |");
			printf("\n|	Transfer	   |");
			printf("\n|	%s		   |", user[j].Riwayat.NamaBank[*i]);
			printf("\n|	%s	   |", user[j].Riwayat.NoRek[*i]);
			printf("\n|	%s	   	   |", user[j].Riwayat.NamaUser[*i]);
			printf("\n|	-Rp. %d	   |", user[j].Riwayat.nominal[*i] );
		}
		else if (user[j].Riwayat.transaksi[*i] == 3){
			printf("\n|			   |");
			printf("\n|	Setor Tunai	   |");
			printf("\n|	+Rp. %d	   |", user[j].Riwayat.nominal[*i]);
		}	
	}
	else if(bhs == 2){
		if (user[j].Riwayat.transaksi[*i] == 1){
			printf("\n|			   |");
			printf("\n|	Withdrawal	   |");
			printf("\n|	-Rp. %d	   |", user[j].Riwayat.nominal[*i]);
		}
		else if (user[j].Riwayat.transaksi[*i] == 2){
			printf("\n|			   |");
			printf("\n|	Transfer	   |");
			printf("\n|	%s		   |", user[j].Riwayat.NamaBank[*i]);
			printf("\n|	%s	   |", user[j].Riwayat.NoRek[*i]);
			printf("\n|	%s	   	   |", user[j].Riwayat.NamaUser[*i]);
			printf("\n|	-Rp. %d	   |", user[j].Riwayat.nominal[*i] );
		}
		else if (user[j].Riwayat.transaksi[*i] == 3){
			printf("\n|			   |");
			printf("\n|	Cash Deposit	   |");
			printf("\n|	+Rp. %d	   |", user[j].Riwayat.nominal[*i]);
		}	
	}
}

void displaySaldoAtmHabis(int bhs){
	header();
 	if (bhs == 1){
    printToxy(46,3,"UNTUK SEMENTARA TRANSAKSI");
	printToxy(48,4,"TIDAK DAPAT DIPROSES");
	printToxy(45,9,"PERLU TRANSAKSI YANG LAIN");
	printToxy(90,13,"YA");
	printToxy(90,17,"TIDAK");
	}
 	else if(bhs == 2){
	printToxy(46,3,"FOR THE TIME THE TRANSACTION ");
	printToxy(48,4,"CANNOT BE PROCESSED");
	printToxy(45,9,"NEED ANOTHER TRANSACTION");
	printToxy(90,9,"YES");
	printToxy(90,17,"NO");
	}
	
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");			
}

void displayAkunDisable(int bhs){
	header();
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(41,3,"MOHON MAAF UNTUK SEMENTARA KARTU ANDA");
		printToxy(48,4,"TELAH DISABLED/NONAKTIF");
		printToxy(42,5,"=================================");
		printToxy(33,7,"UNTUK SEMENTARA ANDA TIDAK DAPAT MELAKUKAN TRANSAKSI");
		printToxy(38,8,"APAKAH ANDA INGIN ENABLE/REAKTIVASI KARTU ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"Masukkan pilihan anda: ");
	}
	if (bhs == 2){
		printToxy(43,3,"SORRY FOR TEMPORARILY YOUR CARD");
		printToxy(50,4,"HAS BEEN DISABLED");
		printToxy(42,5,"=================================");
		printToxy(38,7,"TEMPORARILY YOU CANNOT MAKE TRANSACTIONS");
		printToxy(38,8,"DO YOU WANT TO ENABLE/REACTIVATE THE CARD ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"Enter Your Choice: ");
	}		
}

void displayEnableTanggalLahir(int bhs){
	header();
	printToxy(42,5,"=================================");
	printToxy(7,9,"[1] =>");
	printToxy(45,12,"___________________________");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(41,3,"MOHON MAAF UNTUK SEMENTARA KARTU ANDA");
		printToxy(48,4,"TELAH DISABLED/NONAKTIF");
		printToxy(37,7,"UNTUK MELAKUKAN ENABLE/REAKTIVASI KARTU ANDA");
		printToxy(41,8,"SILAHKAN MASUKKAN TANGGAL LAHIR ANDA");
		printToxy(50,9,"FORMAT (DD MM YY)");
		printToxy(90,13,"BENAR");
		printToxy(90,17,"SALAH");
	}
	if (bhs == 2){
		printToxy(43,3,"SORRY FOR TEMPORARILY YOUR CARD");
		printToxy(50,4,"HAS BEEN DISABLED");
		printToxy(43,7,"TO ENABLE/REACTIVATE YOUR CARD");
		printToxy(42,8,"PLEASE ENTER YOUR DATE OF BIRTH");
		printToxy(50,9,"FORMAT (DD MM YY)");
		printToxy(90,13,"TRUE");
		printToxy(90,17,"FALSE");
	}		
}

void displayEnableTanggalLahirSalah3x(int bhs){
	header();
	printToxy(42,5,"=================================");
	printToxy(45,12,"___________________________");
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(41,3,"MOHON MAAF UNTUK SEMENTARA KARTU ANDA");
		printToxy(48,4,"TELAH DISABLED/NONAKTIF");
		printToxy(37,7,"UNTUK MELAKUKAN ENABLE/REAKTIVASI KARTU ANDA");
		printToxy(41,8,"SILAHKAN MASUKKAN TANGGAL LAHIR ANDA");
		printToxy(50,9,"FORMAT (DD/MM/YY)");
		
		printToxy(47,15,"TANGGAL LAHIR ANDA SALAH ");
		printToxy(34,16,"SILAKAN MASUKKAN KEMBALI TANGGAL LAHIR YANG BENAR");
		printToxy(50,17,"ANDA AKAN KELUAR");
		printToxy(45,18,"BILA ANDA SALAH 3(TIGA) KALI");
		printToxy(90,13,"BENAR");
		printToxy(90,17,"SALAH");
	}
	if (bhs == 2){
		printToxy(43,3,"SORRY FOR TEMPORARILY YOUR CARD");
		printToxy(50,4,"HAS BEEN DISABLED");
		printToxy(43,7,"TO ENABLE/REACTIVATE YOUR CARD");
		printToxy(42,8,"PLEASE ENTER YOUR DATE OF BIRTH");
		printToxy(50,9,"FORMAT (DD/MM/YY)");
		
		printToxy(45,15,"YOUR DATE OF BIRTH IS WRONG");
		printToxy(40,16,"PLEASE REENTER CORRECT DATE OF BIRTH ");
		printToxy(52,17,"YOU WILL EXIT");
		printToxy(45,18,"IF YOU WRONG 3(THREE) TIMES");
		printToxy(90,13,"TRUE");
		printToxy(90,17,"FALSE");
	}
}

void displayEnableBerhasil(int bhs){
	header();
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(46,3,"KARTU ANDA TELAH BERHASIL");
		printToxy(48,4,"DI ENABLED/REAKTIVASI");
		printToxy(42,5,"=================================");
		printToxy(39,9,"APAKAH ANDA INGIN LANJUTKAN TRANSAKSI ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"Masukkan pilihan anda: ");
	}
	if (bhs == 2){
		printToxy(43,3,"YOUR CARD HAS BEEN SUCCESSFULLY");
		printToxy(50,4,"ENABLED/REACTIVATED");
		printToxy(42,5,"=================================");
		printToxy(39,9,"DO YOU WANT TO CONTINUE THE TRANSACTION ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"Enter Your Choice: ");
	}		
}

void displayEnable(int bhs){
	header();
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(42,3,"KARTU ANDA TELAH BERSTATUS ENABLED");
		printToxy(42,5,"=================================");
		printToxy(40,9,"APAKAH ANDA INGIN LANJUTKAN TRANSAKSI ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"Masukkan pilihan anda: ");
	}
	if (bhs == 2){
		printToxy(43,3,"YOUR CARD HAS STATUS ENABLED");
		printToxy(42,5,"=================================");
		printToxy(39,9,"DO YOU WANT TO CONTINUE THE TRANSACTION ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"Enter Your Choice: ");
	}		
}

void displayEnableGagal(int bhs){
	header();
	printToxy(7,9,"[1] =>");
	printToxy(7,13,"[2] =>");
	printToxy(7,17,"[3] =>");
	printToxy(105,9,"<= [4]");
	printToxy(105,13,"<= [5]");
	printToxy(105,17,"<= [6]");
	if (bhs == 1){
		printToxy(39,3,"KARTU ANDA GAGAL UNTUK ENABLE/REAKTIVASI");
		printToxy(42,5,"=================================");
		printToxy(41,8,"SAAT INI STATUS KARTU ANDA DISABLED");
		printToxy(44,9,"APAKAH ANDA INGIN LANJUTKAN ?");
		printToxy(90,13,"YA");
		printToxy(90,17,"TIDAK");
		printToxy(60,24,"Masukkan pilihan anda: ");
	}
	if (bhs == 2){
		printToxy(40,3,"YOUR CARD FAILED TO ENABLE/REACTIVATE");
		printToxy(42,5,"=================================");
		printToxy(38,8,"AT THIS TIME YOUR CARD STATUS IS DISABLED");
		printToxy(46,9,"DO YOU WANT TO CONTINUE ?");
		printToxy(90,13,"YES");
		printToxy(90,17,"NO");
		printToxy(60,24,"Enter Your Choice: ");
	}
}
