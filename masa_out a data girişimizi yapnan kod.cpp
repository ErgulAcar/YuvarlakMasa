//15:35 saat 13.11.21 tarih yazar Ergül ACAR
//masa_in den dosyayý satýr satýr okuup satýr satýr düðüme eklicek ve yuvarlak masa oyunumuz gerçekleþecek 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>//rand ve srand fonksiyonu için
#include<locale.h>//setlocale fonksiyonu için
#include <unistd.h>//sleep fonk ve system fonk var

//düðüm yapýsý
struct node
{
	long int sayi;
	struct node *onceki;//önceki düðümü iþaret eder
	struct node *sonraki;//sonraki düðümü iþaret eder
};

struct node* basla = NULL;//program baþladýðýnda veri veya data olmadýðýndan null atýyoruz.
struct node* sonu = NULL;//program baþladýðýnda veri veya data olmadýðýndan null atýyoruz.
//düðüm yapýsý oluþturma
struct node* dugumOlustur(long int sayi)
{
	struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));//malloc ile ramde düðüm ayýrýyoruz
	yeniDugum->sayi = sayi;//sayi datasýný yenidüðümün sayisýna atýyorum
	yeniDugum->onceki = NULL;//önceki düðüm iþaretcisini null atýyoruz
	yeniDugum->sonraki = NULL;//sonraki düðüm iþaretcisini null atýyoruz
	
	return yeniDugum;//yenidüðümü döndürüyor
}

void ekle(long int);
int say(struct node*);
void yuvarlakMasa();


int main()
{//mainin baþý
	setlocale(LC_ALL, "Turkish");//tr karakter giriþi için fonksiyon
	printf("Merhaba Hoþgeldizin...\nSistem Yükleniyor...\n");//süsleyiþ
	sleep(1);//burda bekletmek için bir fonksiyon
	system("CLS");//Ekrandaki her þeyin silinmesi saðlanmaktadýr. ekran kalabalýk olmasýn diye
	FILE *masa_in;
	if ((masa_in = fopen("masa_in.txt", "r")) == NULL) //dosya yoksa hata verip kapatsýn diye if fonk.
	{
      printf("masa_in e data giriþi.cpp dosyasýnýn ilk çalýþtýrýnýz!\n");
      exit(1);//düzgün çalýþmadan kapandý hatasý
	}
	fclose(masa_in);//dosya kaapatma iþlemi
	printf("Dosya bulundu...\nAktarýlýyor...");//süs kullanýcýyý oyalama
	sleep(1);//burda bekletmek için bir fonksiyon
	system("CLS");//Ekrandaki her þeyin silinmesi saðlanmaktadýr. ekran kalabalýk olmasýn diye
  	masa_in = fopen("masa_in.txt", "r");//dosya açma, "r" ile dosya okuma yapýlýr /dosya mevcut olmalu
  	long int sayi=0;//satýr okurken char ile okuyoruz charý sayýya cevirirken lazým olacak
	while(!feof(masa_in) )//dosya sonuna kadar devam eden bir döngü
	{
		char ch[7];//1-1000000 arasý olduðu için bana 7 haneli veri yeterli
		fgets(ch,7,masa_in);// dosyadan satýr okuma iþlemi
		if(atoi(ch)==0)//satýr sonu char giden veri 0 olur bu da demek oluyorki tüm veriler alýndý 
		{
			break;//bitir
		}
		else//deðil ise
		{
			sayi=atoi(ch);//karakteri sayýya cevir
			ekle(sayi);//ekle fonksiyonunu caðýr.
		}
	}
	fclose(masa_in);//dosya kapatma
	printf("Aktarma tamamlandý...\n");//süs
	printf("Yuvarlak masa oyunu baþladý...\n");//süs
	yuvarlakMasa();//fonksiyon caðrýsý
	printf("masa_out.txt dosyasýna sonuçlar yazdýrýlmýþtýr...\niyi günler...");// iþlem baþarýlý sonuçlandýðýný dongü baþarýlý bittiðini gösteren bir yazý daha
	
	return 0;
}//mainin sonu

void ekle(long int sayi)
{//ekle fonk baþý
	struct node* sonaEkle = dugumOlustur(sayi);//dugumoluþtur fonksiyonu ile düðümü oluþturuyoruz
	if(basla == NULL)//ilk giridi ile baslaya eklesin diye if else oluþturdum
	{
		basla = sonaEkle;//balsaya sanaekleyi atýyorum
	}
	else//veri varsa dolaþva iþlemi yani traverse yapýyoruz
	{
		struct node* geciciSayi = basla;//gecici bir deðer oluþturdum baslayý atadým
		//düðümde dolaþma iþlemi
		while(geciciSayi->sonraki != NULL)//geciciSayi->sonraki boþ olana kadar devam edecek
		{
			geciciSayi = geciciSayi->sonraki;//sonraki sayiyi gecicisayiya aatýyorum
		}
		sonaEkle->onceki = geciciSayi;//sonraki sayiyi gecici yapmýþtýk yani önceki sayida gecicisayimiz olduðu için onceki ye gecicisayiyi atýyorum
		geciciSayi->sonraki = sonaEkle;//sonaekle deðiþkenimiz fonksiyona girilen datamýz olduðu için onuda sona ekliyorum
		//düðümün sonraki elemanýný birdaha null atamama gerek yok zaten üstte null atamýþtým
		sonu=sonaEkle;//sonu olan struct verimizi nulldan cýkarýyoruz sonaEkleye eþitliyoruz
	}
}//ekle fonk Sonu

int say(struct node* ilksayi)
{//say fonk baþý
	int sayac=0;
	if(ilksayi->sonraki ==ilksayi)
		sayac++;
	return sayac;
}//say fonk sonu

void yuvarlakMasa()
{//yuvarlakMasa fonk baþý
	int dur=1;//while den cýkmamýzý saðlayacak data
	struct node* ilkSayi = basla;//baþlayý ilksayi structna atýyorum
	long int sayar;//sayar datasý bizim for dongüleri için lazým olacak
	//ilk sayýmýzý dosyaya yazdýk
	FILE *masa_out = fopen("masa_out.txt", "w");//dosya açma, "w" ile dosya oluþturma var ise içeriðini sil
	fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datamýzý masa_out.txt dosyasýna yazýyoruz.
	fclose(masa_out);//dosya kapatma
	sonu->sonraki=basla;//sonu ve baþý baðladým yaný olay þu 1 2 3 4 5 olsun. 5 ten sonra veri yok normalde baðlý listede ama ben 
						//5 in sonraki iþaretcisini 1 e baðladým böylece ileriyonde 1-2-3-4-5-1-2-3-4-5-1-.. diye gidicek
	basla->onceki=sonu;//üsteki iþlemin tersini yaptým bu sefer geri yonde 5-4-3-2-1-5-4-3-2-1-5-4.. diye gidicek bu iþlem forda uðraþmayalým diye yaptýðým bir iþlem
	
	sayar = ilkSayi->sayi;//sayar ilksayinin rakamýný tutuyor
	//aslýnda buradan alttaki iþlemleri bir fonk cekebilriz ama ben hata aldýðým için cekmedim.
	struct node* onceki = ilkSayi->onceki;//ilk sayýyý cýkartýcaðýz onun için önceki
	struct node* sonraki = ilkSayi->sonraki;// ve sonraki elemanlarýn iþaretçilerini baðlamak için bize lazým
	free(ilkSayi);//ilksayiyi cýkarttýk
	if(sayar%2==0)//eðer çift ise 
	{//söyleki 2 3 4 5 1 olsun biz 2 cýkarttýk 3 4 5 1 saymada 3 dahil etmez 3 alsak normalde 4 bir sonraki eleman olmasý gerekirken 5 olur bu hatala karþýlaþmamak için bunu yaptým
		ilkSayi = onceki;//ilk sayýyý önceki ilan ettim
		ilkSayi->sonraki = sonraki;// ilk sayi 1 oldu ve birin sonraki iþaretcisi normalde 2 yi tutuyor biz onu 3 gösteriyoruz burda
		sonraki->onceki = ilkSayi;//3 te ise ilk iþaretcisi 2 yi göstteriyor bu seferde onu 1 e baðlýyoruz bu sefer dongü 3-4-5-1-3-4-5-1-.. diye gidicek 2 cýkttý 
	}
	else//deðil ise tekktir
	{//bu sefer ise 1 3 4 5 2 sayýlarýmýz 1 cýkýnca 3 4 5 2 kalýyor sonraki cýkacak 2 olmalý onun icin sayýmýn baþlamasý dereken yer 3 oluyor geriye doðru cýkan sayý kadar adým atýnca 2 cýkýyor böylelikle
		ilkSayi = sonraki;//saymaya baþlýcaðýmýz sayýyý 3 ilan ediyoruz
		ilkSayi->onceki = onceki;//önceki iþaretci 1 i gösteriyordu onu cýkarttýk bize sonu göstermeli yani 2 yi iþarett ettiriyoruz
		onceki->sonraki = ilkSayi;//oncekinin sonraki yaný 2 ->1 iþaret ediyordu 1 cýkttý o zaman 2->3 iþaret edicek bizde onu yaptýk burda
	}
	
	while(1)//sonsuz bir dongu break görene kadar
	{
		if(dur==say(ilkSayi))//say fonksiyonu baðlý listede son 1 eleman kaldýðýný gösteriyor bize dur þuan 1 
		{//dura eþit olursa demmekki son eleman içinde iþlem yapýyoruz bu turdan sonra whiledan cýkmalýyýz demkketir
			dur++;	//duru aþaðda lazým olacaðý için 2 yapýyoruz
		}
		
		if((sayar%2)==0)//çift ise donecek sayýmýz
		{
			for(long int i=0 ; i<sayar ; i++)//bi donecek sayýmýz kadar donduruyoruz
			{
				ilkSayi=ilkSayi->sonraki;//çift ise ileriye doðru kurall bizde ileri iþaretcilerimizi kullanarak geziyoruz
			}//en sonunda bulduk bu bizim sonraki cýkan sayýmýz olacak bunun out.txt yazýcaðýz bu sefer
			FILE *masa_out = fopen("masa_out.txt", "a");//dosya açma, "a" ile ekleme yapar yok ise oluþturur.
			fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datamýzý masa_out.txt dosyasýna yazýyoruz.
			fclose(masa_out);//dosya kapatma
			sayar = ilkSayi->sayi;//sayarýmýz donuþ  sayýmýzdýr bu sefer kurral cýkan oyuncu kadar ileri veya geri olduðu için datamýzda bu sefer cýkarný tutuyoruz
			struct node* onceki = ilkSayi->onceki;//onceki ve
			struct node* sonraki = ilkSayi->sonraki;//sonraki elemanlarý yukardaki iþlemin aynýsýný yapmak için alýyoruz
			free(ilkSayi);//sayýyý cýkartýyoruz
			if(sayar%2==0)//cifttmi
			{
				ilkSayi = onceki;//üstte yaptýðýmýz iþlemin aynýsý
				ilkSayi->sonraki = sonraki;
				sonraki->onceki = ilkSayi;
			}
			else//tekmi
			{//ayný þekilde 
				ilkSayi = sonraki;
				ilkSayi->onceki = onceki;
				onceki->sonraki = ilkSayi;
			}//bunun iiçin fonk kullanýcaktýmda ufak bi hata aldým hatamý bulamadým bende kopyyala yapýþtýr yaparak devam etttim 
		}
		
		else//tek
		{//ciftt te anlattýðým iþlemlerin aynýsý tek farký dolaþým geri yonde
			for(long int i=0 ; i<sayar ; i++)
			{
				ilkSayi=ilkSayi->onceki;
			}
			FILE *masa_out = fopen("masa_out.txt", "a");//dosya açma, "a" ile ekleme yapar yok ise oluþturur.
			fprintf(masa_out,"%ld\n",ilkSayi->sayi);//datamýzý masa_out.txt dosyasýna yazýyoruz.
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
		
		if(dur==2)//duru son eleman a geldiðimizde 2 yapmýþtýk bir daha donmesin diye
		{
			break;	//whileden cýkartýyoruz..
		}
	}
}//yuvarlakMasa fonk sonu
