//saat 12:24 13.11.2021 tarih yazar Ergül ACAR
//burada kullanýcýnýn girdiði n sayisýný alýyoruz kullanýcýdan ve 1 den n e kadar sayiyi ratgele olarak masa_in.txt aktarýyoruz
#include <stdio.h>
#include <stdlib.h>//rand ve srand fonksiyonu için
#include<locale.h>//setlocale fonksiyonu için
#include <unistd.h>//sleep fonk ve system fonk var
#include <time.h> //time fonksiyonu için

// setlocale(LC_ALL, "Turkish");

void kontroll(long int);//kontrol fonksiyonu 1<sayi<1000000 arasýndamý diye kontrol ettiriyoruz 
long int randd(long int);//rand fonksiyonu barýndýrýyor böylelikle her defasýnda rand fomksiyonunu yazmak yerine randd fonksiyonu çaðýmamýz yeterli oluyor
long int rand_atama(long int,long int [],long int);//sayilarýn tekrar etmemesini saðlýyoruz burda

int main()
{//main baþlangiç
	setlocale(LC_ALL, "Turkish");//tr karakter giriþi için fonksiyon
	long int adet;//1 000 000 u da tutabilsin diye datayý long int tanýmladým
	printf("Lütfen 1 ile 1 000 000 arasýnda bir sayi giriniz->> ");
	scanf("%ld", &adet);//kullanýcýdan sayi istiyoruz
	kontroll(adet);//kontrol fonksiyonu çaðýrýyoruz
	long int sayilar[adet];//adet kadar uzunlukta dizi datasý atýyoruz yine long int olarak 1000000 tutabilsin diye
	printf("Sayilar dosyaya rantom aktarýlýyor...\n");
	sleep(1);//burda bekletmek için bir fonksiyon
	srand(time(NULL));//program her çalýþtýðýnda farklý sayýlar tutsun diye bir fonk.
	for(long int i = 0 ; i < adet ; i++)//adet kadar dönen bir for döngüsü
	{
		if(i==0)//ilk sayiyi diret olarak kontrol etmesin diye ayýrýyoruz
		{
			sayilar[i] = randd(adet);//randd fonksiyonu deðer dönen bir fonk olduðu için diret sayilar[i] atýyoruz
		}
		else//geri kalanlarý kontrol etmesi için rand_atama fonksiyonundan yardým alarak atýyoruz
		{
			sayilar[i] = rand_atama(adet,sayilar,i);//rand_atama fonksiyonu deðer dönen bir fonk olduðu için diret sayilar[i] atýyoruz
			
		}
	}
	//buradan sonrasý dosya oluþtur yaz kapa v.b iþler
	FILE *masa_in = fopen("masa_in.txt", "w");//dosya açma, "w" ile dosya oluþturma var ise içeriðini sil
	for(long int z = 0 ; z < adet ; z++)//tüm datalarýmýz sayilar[adet] kadar olduðu için for dongüsü
	{
		if((z+1)==adet)//burdaki if else in amacý son satýrdan sonra bir alt satýra geçmesin çünkü okuma yaparken satýr satýr yapýlacak boþ satýr olusa öncekini tekrar eder.
			fprintf(masa_in,"%ld",sayilar[z]);//datamýzý masa_in.txt dosyasýna yazýyoruz.
		else
			fprintf(masa_in,"%ld\n",sayilar[z]);//datamýzý masa_in.txt dosyasýna yazýyoruz.
	}
	fclose(masa_in);//dosya kapatma
	printf("Ýþlem Baþarlý...\nÝyi Yine Bekleriz :D");//bittiðini belirtiyoruz 

	return 0;//main bitiþi
}

void kontroll(long int adet)//yukarda tanýmladýðýmýz fonksiyonu dolduruyoruz burda
{//kontroll fonk baþý
	setlocale(LC_ALL, "Turkish");//tr karakter giriþi için fonksiyon
	while(1)//burda sonsuz bir döngü yaptým çünkü istenileni girmediði sürece donsun istiyorum
	{
		if(adet>0 && adet<=1000000)//istenilen aralýk ise
		{
			break;//while den cýksýn
		}
		else//deðilse devamm
		{
			printf("1 ile 1 000 000 arasýnda sayi girmediniz...\n Tekrar deneyin... ");//güzel bir hata mesajý
			sleep(1);//burda bekletmek için bir fonksiyon
			system("CLS");//Ekrandaki her þeyin silinmesi saðlanmaktadýr. ekran kalabalýk olmasýn diye
			printf("Lütfen 1 ile 1 000 000 arasýnda bir sayi giriniz->> ");//temiz ekrana tekrar sorumuzu sorduruyorum
			scanf("%ld", &adet);//girdiði adete atýyorum
		}
	}
}//kontroll fonk sonu

long int randd(long int adet)//yukarda tanýmladýðýmýz fonksiyonu dolduruyoruz burda
{//randd fonk baþý
	return rand() * rand() % adet + 1;//adet ve 1 aralýðýnda rastgele sayý tutan bir donksiyon dönüyor
}//randd fonk sonu

long int rand_atama(long int adet,long int sayilar[] ,long int i)//yukarda tanýmladýðýmýz fonksiyonu dolduruyoruz burda
{//rand_atama fonk baþý
	srand(time(NULL));//program her çalýþtýðýnda farklý sayýlar tutsun diye bir fonk.eðer bunu dongu içinde yazsam hep ayný sayýyý tekrar edecekti bildiðimden deðil deneyimden öðrendim
	while(1)//burda sonsuz bir döngü yaptým çünkü tekrar etmeyen sayýyý bulana kadar devam etsin
	{
		long int sayac=0;//datayý içinde tanýmlama amaçým eðer birkere bile artsa donguden cýkamaz ve tekrardan sýfýrlamam lazým bende içinde tanýmladým dýþarda tanýmlayýp burada tekrardan 0 a eþitleye bilridim ama buda ayrý bir yontem
		long int deneme = randd(adet);//deneme datasýný deniyorum rastgele sayý vererek
		for(long int k=0; k<i ; k++)//burda girdiðimiz sayýlarýn öncesini kontrol ediceðiz onun için bana i kadar donmesi yeterli i zaten þuan atýcaðýmýz sayi
		{ 
			if(deneme == sayilar[k])//önceki sayilara eþittmi? ise
			{
				sayac++;//sayaç bir arttsýn
			}
		}
		if(sayac==0)//sayaç eþitlik hiç olmamýþ ise bizim istediðim yani deneme hiç kullanmadýðýmýz bir data olduðu için bu deðeri dondürrebiliriz
		{
			return deneme;//deneme denüyor bu fonksiyonumuz
		}
		//eðer ife girmediyse demek oluyorki sayaç 0 dan büyük buda demek oluyorki randd ile verilen deneme datasý önceden varmýþ sar baþa while if e girene kadar...
	}
}//rand_atama fonk sonu
