//saat 12:24 13.11.2021 tarih yazar Erg�l ACAR
//burada kullan�c�n�n girdi�i n sayis�n� al�yoruz kullan�c�dan ve 1 den n e kadar sayiyi ratgele olarak masa_in.txt aktar�yoruz
#include <stdio.h>
#include <stdlib.h>//rand ve srand fonksiyonu i�in
#include<locale.h>//setlocale fonksiyonu i�in
#include <unistd.h>//sleep fonk ve system fonk var
#include <time.h> //time fonksiyonu i�in

// setlocale(LC_ALL, "Turkish");

void kontroll(long int);//kontrol fonksiyonu 1<sayi<1000000 aras�ndam� diye kontrol ettiriyoruz 
long int randd(long int);//rand fonksiyonu bar�nd�r�yor b�ylelikle her defas�nda rand fomksiyonunu yazmak yerine randd fonksiyonu �a��mam�z yeterli oluyor
long int rand_atama(long int,long int [],long int);//sayilar�n tekrar etmemesini sa�l�yoruz burda

int main()
{//main ba�langi�
	setlocale(LC_ALL, "Turkish");//tr karakter giri�i i�in fonksiyon
	long int adet;//1 000 000 u da tutabilsin diye datay� long int tan�mlad�m
	printf("L�tfen 1 ile 1 000 000 aras�nda bir sayi giriniz->> ");
	scanf("%ld", &adet);//kullan�c�dan sayi istiyoruz
	kontroll(adet);//kontrol fonksiyonu �a��r�yoruz
	long int sayilar[adet];//adet kadar uzunlukta dizi datas� at�yoruz yine long int olarak 1000000 tutabilsin diye
	printf("Sayilar dosyaya rantom aktar�l�yor...\n");
	sleep(1);//burda bekletmek i�in bir fonksiyon
	srand(time(NULL));//program her �al��t���nda farkl� say�lar tutsun diye bir fonk.
	for(long int i = 0 ; i < adet ; i++)//adet kadar d�nen bir for d�ng�s�
	{
		if(i==0)//ilk sayiyi diret olarak kontrol etmesin diye ay�r�yoruz
		{
			sayilar[i] = randd(adet);//randd fonksiyonu de�er d�nen bir fonk oldu�u i�in diret sayilar[i] at�yoruz
		}
		else//geri kalanlar� kontrol etmesi i�in rand_atama fonksiyonundan yard�m alarak at�yoruz
		{
			sayilar[i] = rand_atama(adet,sayilar,i);//rand_atama fonksiyonu de�er d�nen bir fonk oldu�u i�in diret sayilar[i] at�yoruz
			
		}
	}
	//buradan sonras� dosya olu�tur yaz kapa v.b i�ler
	FILE *masa_in = fopen("masa_in.txt", "w");//dosya a�ma, "w" ile dosya olu�turma var ise i�eri�ini sil
	for(long int z = 0 ; z < adet ; z++)//t�m datalar�m�z sayilar[adet] kadar oldu�u i�in for dong�s�
	{
		if((z+1)==adet)//burdaki if else in amac� son sat�rdan sonra bir alt sat�ra ge�mesin ��nk� okuma yaparken sat�r sat�r yap�lacak bo� sat�r olusa �ncekini tekrar eder.
			fprintf(masa_in,"%ld",sayilar[z]);//datam�z� masa_in.txt dosyas�na yaz�yoruz.
		else
			fprintf(masa_in,"%ld\n",sayilar[z]);//datam�z� masa_in.txt dosyas�na yaz�yoruz.
	}
	fclose(masa_in);//dosya kapatma
	printf("��lem Ba�arl�...\n�yi Yine Bekleriz :D");//bitti�ini belirtiyoruz 

	return 0;//main biti�i
}

void kontroll(long int adet)//yukarda tan�mlad���m�z fonksiyonu dolduruyoruz burda
{//kontroll fonk ba��
	setlocale(LC_ALL, "Turkish");//tr karakter giri�i i�in fonksiyon
	while(1)//burda sonsuz bir d�ng� yapt�m ��nk� istenileni girmedi�i s�rece donsun istiyorum
	{
		if(adet>0 && adet<=1000000)//istenilen aral�k ise
		{
			break;//while den c�ks�n
		}
		else//de�ilse devamm
		{
			printf("1 ile 1 000 000 aras�nda sayi girmediniz...\n Tekrar deneyin... ");//g�zel bir hata mesaj�
			sleep(1);//burda bekletmek i�in bir fonksiyon
			system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r. ekran kalabal�k olmas�n diye
			printf("L�tfen 1 ile 1 000 000 aras�nda bir sayi giriniz->> ");//temiz ekrana tekrar sorumuzu sorduruyorum
			scanf("%ld", &adet);//girdi�i adete at�yorum
		}
	}
}//kontroll fonk sonu

long int randd(long int adet)//yukarda tan�mlad���m�z fonksiyonu dolduruyoruz burda
{//randd fonk ba��
	return rand() * rand() % adet + 1;//adet ve 1 aral���nda rastgele say� tutan bir donksiyon d�n�yor
}//randd fonk sonu

long int rand_atama(long int adet,long int sayilar[] ,long int i)//yukarda tan�mlad���m�z fonksiyonu dolduruyoruz burda
{//rand_atama fonk ba��
	srand(time(NULL));//program her �al��t���nda farkl� say�lar tutsun diye bir fonk.e�er bunu dongu i�inde yazsam hep ayn� say�y� tekrar edecekti bildi�imden de�il deneyimden ��rendim
	while(1)//burda sonsuz bir d�ng� yapt�m ��nk� tekrar etmeyen say�y� bulana kadar devam etsin
	{
		long int sayac=0;//datay� i�inde tan�mlama ama��m e�er birkere bile artsa donguden c�kamaz ve tekrardan s�f�rlamam laz�m bende i�inde tan�mlad�m d��arda tan�mlay�p burada tekrardan 0 a e�itleye bilridim ama buda ayr� bir yontem
		long int deneme = randd(adet);//deneme datas�n� deniyorum rastgele say� vererek
		for(long int k=0; k<i ; k++)//burda girdi�imiz say�lar�n �ncesini kontrol edice�iz onun i�in bana i kadar donmesi yeterli i zaten �uan at�ca��m�z sayi
		{ 
			if(deneme == sayilar[k])//�nceki sayilara e�ittmi? ise
			{
				sayac++;//saya� bir artts�n
			}
		}
		if(sayac==0)//saya� e�itlik hi� olmam�� ise bizim istedi�im yani deneme hi� kullanmad���m�z bir data oldu�u i�in bu de�eri dond�rrebiliriz
		{
			return deneme;//deneme den�yor bu fonksiyonumuz
		}
		//e�er ife girmediyse demek oluyorki saya� 0 dan b�y�k buda demek oluyorki randd ile verilen deneme datas� �nceden varm�� sar ba�a while if e girene kadar...
	}
}//rand_atama fonk sonu
