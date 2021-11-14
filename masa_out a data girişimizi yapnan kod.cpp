//15:35 saat 13.11.21 tarih yazar Erg�l ACAR
//masa_in den dosyay� sat�r sat�r okuup sat�r sat�r d���me eklicek ve yuvarlak masa oyunumuz ger�ekle�ecek 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>//rand ve srand fonksiyonu i�in
#include<locale.h>//setlocale fonksiyonu i�in
#include <unistd.h>//sleep fonk ve system fonk var

//d���m yap�s�
struct node
{
	long int sayi;
	struct node *onceki;//�nceki d���m� i�aret eder
	struct node *sonraki;//sonraki d���m� i�aret eder
};

struct node* basla = NULL;//program ba�lad���nda veri veya data olmad���ndan null at�yoruz.
struct node* sonu = NULL;//program ba�lad���nda veri veya data olmad���ndan null at�yoruz.
//d���m yap�s� olu�turma
struct node* dugumOlustur(long int sayi)
{
	struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));//malloc ile ramde d���m ay�r�yoruz
	yeniDugum->sayi = sayi;//sayi datas�n� yenid���m�n sayis�na at�yorum
	yeniDugum->onceki = NULL;//�nceki d���m i�aretcisini null at�yoruz
	yeniDugum->sonraki = NULL;//sonraki d���m i�aretcisini null at�yoruz
	
	return yeniDugum;//yenid���m� d�nd�r�yor
}

void ekle(long int);
int say(struct node*);
void yuvarlakMasa();


int main()
{//mainin ba��
	setlocale(LC_ALL, "Turkish");//tr karakter giri�i i�in fonksiyon
	printf("Merhaba Ho�geldizin...\nSistem Y�kleniyor...\n");//s�sleyi�
	sleep(1);//burda bekletmek i�in bir fonksiyon
	system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r. ekran kalabal�k olmas�n diye
	FILE *masa_in;
	if ((masa_in = fopen("masa_in.txt", "r")) == NULL) //dosya yoksa hata verip kapats�n diye if fonk.
	{
      printf("masa_in e data giri�i.cpp dosyas�n�n ilk �al��t�r�n�z!\n");
      exit(1);//d�zg�n �al��madan kapand� hatas�
	}
	fclose(masa_in);//dosya kaapatma i�lemi
	printf("Dosya bulundu...\nAktar�l�yor...");//s�s kullan�c�y� oyalama
	sleep(1);//burda bekletmek i�in bir fonksiyon
	system("CLS");//Ekrandaki her �eyin silinmesi sa�lanmaktad�r. ekran kalabal�k olmas�n diye
  	masa_in = fopen("masa_in.txt", "r");//dosya a�ma, "r" ile dosya okuma yap�l�r /dosya mevcut olmalu
  	long int sayi=0;//sat�r okurken char ile okuyoruz char� say�ya cevirirken laz�m olacak
	while(!feof(masa_in) )//dosya sonuna kadar devam eden bir d�ng�
	{
		char ch[7];//1-1000000 aras� oldu�u i�in bana 7 haneli veri yeterli
		fgets(ch,7,masa_in);// dosyadan sat�r okuma i�lemi
		if(atoi(ch)==0)//sat�r sonu char giden veri 0 olur bu da demek oluyorki t�m veriler al�nd� 
		{
			break;//bitir
		}
		else//de�il ise
		{
			sayi=atoi(ch);//karakteri say�ya cevir
			ekle(sayi);//ekle fonksiyonunu ca��r.
		}
	}
	fclose(masa_in);//dosya kapatma
	printf("Aktarma tamamland�...\n");//s�s
	printf("Yuvarlak masa oyunu ba�lad�...\n");//s�s
	yuvarlakMasa();//fonksiyon ca�r�s�
	printf("masa_out.txt dosyas�na sonu�lar yazd�r�lm��t�r...\niyi g�nler...");// i�lem ba�ar�l� sonu�land���n� dong� ba�ar�l� bitti�ini g�steren bir yaz� daha
	
	return 0;
}//mainin sonu

void ekle(long int sayi)
{//ekle fonk ba��
	struct node* sonaEkle = dugumOlustur(sayi);//dugumolu�tur fonksiyonu ile d���m� olu�turuyoruz
	if(basla == NULL)//ilk giridi ile baslaya eklesin diye if else olu�turdum
	{
		basla = sonaEkle;//balsaya sanaekleyi at�yorum
	}
	else//veri varsa dola�va i�lemi yani traverse yap�yoruz
	{
		struct node* geciciSayi = basla;//gecici bir de�er olu�turdum baslay� atad�m
		//d���mde dola�ma i�lemi
		while(geciciSayi->sonraki != NULL)//geciciSayi->sonraki bo� olana kadar devam edecek
		{
			geciciSayi = geciciSayi->sonraki;//sonraki sayiyi gecicisayiya aat�yorum
		}
		sonaEkle->onceki = geciciSayi;//sonraki sayiyi gecici yapm��t�k yani �nceki sayida gecicisayimiz oldu�u i�in onceki ye gecicisayiyi at�yorum
		geciciSayi->sonraki = sonaEkle;//sonaekle de�i�kenimiz fonksiyona girilen datam�z oldu�u i�in onuda sona ekliyorum
		//d���m�n sonraki eleman�n� birdaha null atamama gerek yok zaten �stte null atam��t�m
		sonu=sonaEkle;//sonu olan struct verimizi nulldan c�kar�yoruz sonaEkleye e�itliyoruz
	}
}//ekle fonk Sonu

int say(struct node* ilksayi)
{//say fonk ba��
	int sayac=0;
	if(ilksayi->sonraki ==ilksayi)
		sayac++;
	return sayac;
}//say fonk sonu

void yuvarlakMasa()
{//yuvarlakMasa fonk ba��
	int dur=1;//while den c�kmam�z� sa�layacak data
	struct node* ilkSayi = basla;//ba�lay� ilksayi structna at�yorum
	long int sayar;//sayar datas� bizim for dong�leri i�in laz�m olacak
	//ilk say�m�z� dosyaya yazd�k
	FILE *masa_out = fopen("masa_out.txt", "w");//dosya a�ma, "w" ile dosya olu�turma var ise i�eri�ini sil
	fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datam�z� masa_out.txt dosyas�na yaz�yoruz.
	fclose(masa_out);//dosya kapatma
	sonu->sonraki=basla;//sonu ve ba�� ba�lad�m yan� olay �u 1 2 3 4 5 olsun. 5 ten sonra veri yok normalde ba�l� listede ama ben 
						//5 in sonraki i�aretcisini 1 e ba�lad�m b�ylece ileriyonde 1-2-3-4-5-1-2-3-4-5-1-.. diye gidicek
	basla->onceki=sonu;//�steki i�lemin tersini yapt�m bu sefer geri yonde 5-4-3-2-1-5-4-3-2-1-5-4.. diye gidicek bu i�lem forda u�ra�mayal�m diye yapt���m bir i�lem
	
	sayar = ilkSayi->sayi;//sayar ilksayinin rakam�n� tutuyor
	//asl�nda buradan alttaki i�lemleri bir fonk cekebilriz ama ben hata ald���m i�in cekmedim.
	struct node* onceki = ilkSayi->onceki;//ilk say�y� c�kart�ca��z onun i�in �nceki
	struct node* sonraki = ilkSayi->sonraki;// ve sonraki elemanlar�n i�aret�ilerini ba�lamak i�in bize laz�m
	free(ilkSayi);//ilksayiyi c�kartt�k
	if(sayar%2==0)//e�er �ift ise 
	{//s�yleki 2 3 4 5 1 olsun biz 2 c�kartt�k 3 4 5 1 saymada 3 dahil etmez 3 alsak normalde 4 bir sonraki eleman olmas� gerekirken 5 olur bu hatala kar��la�mamak i�in bunu yapt�m
		ilkSayi = onceki;//ilk say�y� �nceki ilan ettim
		ilkSayi->sonraki = sonraki;// ilk sayi 1 oldu ve birin sonraki i�aretcisi normalde 2 yi tutuyor biz onu 3 g�steriyoruz burda
		sonraki->onceki = ilkSayi;//3 te ise ilk i�aretcisi 2 yi g�stteriyor bu seferde onu 1 e ba�l�yoruz bu sefer dong� 3-4-5-1-3-4-5-1-.. diye gidicek 2 c�ktt� 
	}
	else//de�il ise tekktir
	{//bu sefer ise 1 3 4 5 2 say�lar�m�z 1 c�k�nca 3 4 5 2 kal�yor sonraki c�kacak 2 olmal� onun icin say�m�n ba�lamas� dereken yer 3 oluyor geriye do�ru c�kan say� kadar ad�m at�nca 2 c�k�yor b�ylelikle
		ilkSayi = sonraki;//saymaya ba�l�ca��m�z say�y� 3 ilan ediyoruz
		ilkSayi->onceki = onceki;//�nceki i�aretci 1 i g�steriyordu onu c�kartt�k bize sonu g�stermeli yani 2 yi i�arett ettiriyoruz
		onceki->sonraki = ilkSayi;//oncekinin sonraki yan� 2 ->1 i�aret ediyordu 1 c�ktt� o zaman 2->3 i�aret edicek bizde onu yapt�k burda
	}
	
	while(1)//sonsuz bir dongu break g�rene kadar
	{
		if(dur==say(ilkSayi))//say fonksiyonu ba�l� listede son 1 eleman kald���n� g�steriyor bize dur �uan 1 
		{//dura e�it olursa demmekki son eleman i�inde i�lem yap�yoruz bu turdan sonra whiledan c�kmal�y�z demkketir
			dur++;	//duru a�a�da laz�m olaca�� i�in 2 yap�yoruz
		}
		
		if((sayar%2)==0)//�ift ise donecek say�m�z
		{
			for(long int i=0 ; i<sayar ; i++)//bi donecek say�m�z kadar donduruyoruz
			{
				ilkSayi=ilkSayi->sonraki;//�ift ise ileriye do�ru kurall bizde ileri i�aretcilerimizi kullanarak geziyoruz
			}//en sonunda bulduk bu bizim sonraki c�kan say�m�z olacak bunun out.txt yaz�ca��z bu sefer
			FILE *masa_out = fopen("masa_out.txt", "a");//dosya a�ma, "a" ile ekleme yapar yok ise olu�turur.
			fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datam�z� masa_out.txt dosyas�na yaz�yoruz.
			fclose(masa_out);//dosya kapatma
			sayar = ilkSayi->sayi;//sayar�m�z donu�  say�m�zd�r bu sefer kurral c�kan oyuncu kadar ileri veya geri oldu�u i�in datam�zda bu sefer c�karn� tutuyoruz
			struct node* onceki = ilkSayi->onceki;//onceki ve
			struct node* sonraki = ilkSayi->sonraki;//sonraki elemanlar� yukardaki i�lemin ayn�s�n� yapmak i�in al�yoruz
			free(ilkSayi);//say�y� c�kart�yoruz
			if(sayar%2==0)//cifttmi
			{
				ilkSayi = onceki;//�stte yapt���m�z i�lemin ayn�s�
				ilkSayi->sonraki = sonraki;
				sonraki->onceki = ilkSayi;
			}
			else//tekmi
			{//ayn� �ekilde 
				ilkSayi = sonraki;
				ilkSayi->onceki = onceki;
				onceki->sonraki = ilkSayi;
			}//bunun ii�in fonk kullan�cakt�mda ufak bi hata ald�m hatam� bulamad�m bende kopyyala yap��t�r yaparak devam etttim 
		}
		
		else//tek
		{//ciftt te anlatt���m i�lemlerin ayn�s� tek fark� dola��m geri yonde
			for(long int i=0 ; i<sayar ; i++)
			{
				ilkSayi=ilkSayi->onceki;
			}
			FILE *masa_out = fopen("masa_out.txt", "a");//dosya a�ma, "a" ile ekleme yapar yok ise olu�turur.
			fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datam�z� masa_out.txt dosyas�na yaz�yoruz.
			fclose(masa_out);//dosya kapatma
			sayar = ilkSayi->sayi;
			struct node* onceki = ilkSayi->onceki;
			struct node* sonraki = ilkSayi->sonraki;
			free(ilkSayi);
			if(sayar%2==0)
			{
				ilkSayi = onceki;
				ilkSayi->sonraki = sonraki;
				sonraki->onceki = ilkSayi;
			}
			else
			{
				ilkSayi = sonraki;
				ilkSayi->onceki = onceki;
				onceki->sonraki = ilkSayi;
			}
		}
		
		if(dur==2)//duru son eleman a geldi�imizde 2 yapm��t�k bir daha donmesin diye
		{
			break;	//whileden c�kart�yoruz..
		}
	}
}//yuvarlakMasa fonk sonu
