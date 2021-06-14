#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ders{
	char derskodu[10];
	char dersadi[50];
	ders* sonraki;
};

struct ogrenci {
	char ogrno[15];
	char ad[30];
	char soyad[30];
	ders* dersdugumu;
	ogrenci* sonraki;
};

ogrenci* ogrenciler;

void listeKur(string dosyaAdi)
{
	ifstream dosya(dosyaAdi, ios::in);

	if (!dosya)
	{
		cout << "Dosya bulunamadi...\n";
	}
	else
	{
		ogrenci* oncekiOgrenci = NULL;
		char dersKod[25];
		char dersAd[25];

		dosya >> dersKod;
		dosya >> dersAd;

		while (1)
		{
			char middle[25];

			ders* yeniDers = new ders;
			strcpy_s(yeniDers->dersadi, dersAd);
			strcpy_s(yeniDers->derskodu, dersKod);
			yeniDers->sonraki = NULL;

			ogrenci* yeniOgrenci = new ogrenci;

			dosya >> yeniOgrenci->ogrno;
			if (!(yeniOgrenci->ogrno[0] >= 48 && yeniOgrenci->ogrno[0] <= 57))
			{
				strcat_s(oncekiOgrenci->ad, " ");
				strcat_s(oncekiOgrenci->ad, oncekiOgrenci->soyad);
				strcpy_s(oncekiOgrenci->soyad, oncekiOgrenci->ogrno);
				dosya >> oncekiOgrenci->ogrno;
			}
			dosya >> oncekiOgrenci->ad;
			if (strcmp(oncekiOgrenci->ad, "ONDER") == 0)
			{
				cout << "Hello";
			}

			dosya >> oncekiOgrenci->soyad;
			yeniOgrenci->sonraki = NULL;
			yeniOgrenci->dersdugumu = NULL;

			oncekiOgrenci = yeniOgrenci;

			ogrenci* temp = ogrenciler;

			if (ogrenciler == NULL)
			{
				ogrenciler = yeniOgrenci;
				ogrenciler->dersdugumu = yeniDers;
			}
			else
			{
				bool ogrenciSayisi = false;

				while (temp != NULL)
				{
					if (strcmp(temp->ogrno, yeniOgrenci->ogrno) == 0)
					{
						ogrenciSayisi = true;
						ders* tempDers = temp->dersdugumu;

						while (tempDers->sonraki != NULL)
							tempDers = tempDers->sonraki;
						tempDers->sonraki = yeniDers;

						break;
					}
					temp = temp->sonraki;
				}

				if (!ogrenciSayisi)
				{
					temp = ogrenciler;
					while (temp->sonraki != NULL)
					{
						temp = temp->sonraki;
					}

					temp->sonraki = yeniOgrenci;
					temp->sonraki->dersdugumu = yeniDers;
				}
			}

			if (dosya.eof())
				break;

			yeniDers = NULL;
			yeniOgrenci = NULL;
			temp = NULL;

			delete temp;
			delete yeniDers;
			delete yeniOgrenci;
		}
        dosya.close();
		oncekiOgrenci = NULL;

		delete oncekiOgrenci;
	}
}
void dersSil()
{
	if (ogrenciler == NULL)
	{
		cout << "Listede herhangi bir ogrenci bulunmamaktadir...\n";
	}
	else
	{
		bool dersSilindi = false;
		char kullanici_ogrenciNo[25];
		char kullanici_dersKod[25];

		cout << "Ogrenci numarasini giriniz: ";
		cin >> kullanici_ogrenciNo;
		cout << "Silmek istediginiz ders kodunu giriniz: ";
		cin >> kullanici_dersKod;

		ogrenci* temp = ogrenciler;

		int sonuc = strcmp(temp->ogrno, kullanici_ogrenciNo);

		if (sonuc != 0)
		{
			while (temp != NULL)
			{
				sonuc = strcmp(temp->ogrno, kullanici_ogrenciNo);
				if (sonuc == 0)
					break;
				temp = temp->sonraki;
			}
		}
        
		ders* tempDers = temp->dersdugumu;
		if (tempDers == NULL)
			cout << "Ogrenci adina kayitli herhangi bir ders bulunmamaktadir...\n";
		else
		{
			int sonuc = strcmp(tempDers->derskodu, kullanici_dersKod);
			if (sonuc == 0)
			{
				temp->dersdugumu = tempDers->sonraki;
				tempDers->sonraki = NULL;
				delete tempDers;
				dersSilindi = true;
			}
			else
			{
				while (tempDers->sonraki != NULL)
				{
					int sonuc = strcmp(tempDers->sonraki->derskodu, kullanici_dersKod);
					if (sonuc == 0)
						break;
					tempDers = tempDers->sonraki;
				}
                ders* silinecekDers = tempDers->sonraki;
				tempDers->sonraki = silinecekDers->sonraki;
				silinecekDers->sonraki = NULL;
				delete silinecekDers;
				dersSilindi = true;
			}
		}
        if (dersSilindi)
			cout << kullanici_dersKod << " kodlu ders basariyla silindi...\n";
		else
			cout << kullanici_dersKod << " ders kaydi bulunamadi...\n";
	}
}
void ogrenciSil()
{
	if (ogrenciler == NULL)
	{
		cout << "Listede herhangi bir ogrenci bulunmamaktadir...\n";
	}
	else
	{
		bool ogrenciSilindi = false;
		char kullanici_ogrenciNo[25];
		cout << "Silmek istediginiz ogrenci numarasini giriniz: ";
		cin >> kullanici_ogrenciNo;

		ogrenci* temp = ogrenciler;

		int sonuc = strcmp(temp->ogrno, kullanici_ogrenciNo);
		if (sonuc == 0)
		{
			ogrenciler = temp->sonraki;
			temp->sonraki = NULL;
			delete temp->dersdugumu;
			delete temp;
			ogrenciSilindi = true;
		}
		else
		{
			while (temp->sonraki != NULL)
			{
				sonuc = strcmp(temp->sonraki->ogrno, kullanici_ogrenciNo);
				if (sonuc == 0)
					break;
				temp = temp->sonraki;
			}
			ogrenci* silinecekOgrenci = temp->sonraki;
			temp->sonraki = silinecekOgrenci->sonraki;
			silinecekOgrenci->sonraki = NULL;
			delete silinecekOgrenci->dersdugumu;
			delete silinecekOgrenci;
			ogrenciSilindi = true;
		}

		if (ogrenciSilindi)
			cout << kullanici_ogrenciNo << " numarali ogrenci basariyla silindi...\n";
		else
			cout << kullanici_ogrenciNo << " numarali ogrenci listede bulunamadi...\n";
	}
}

void listele()
{
	ogrenci* tempOgrenci = ogrenciler;
	ders* tempDers = NULL;
	while (tempOgrenci != NULL)
	{
		cout << endl << tempOgrenci->ogrno << " " << tempOgrenci->ad << " " << tempOgrenci->soyad << ": ";
		tempDers = tempOgrenci->dersdugumu;
		while (tempDers != NULL)
		{
			cout << tempDers->derskodu << " " << tempDers->dersadi << " - ";
			tempDers = tempDers->sonraki;
		}
		tempOgrenci = tempOgrenci->sonraki;
	}
	delete tempOgrenci;
	delete tempDers;
}
void ara()
{
	char secim;
	bool ogrenciBulundu = false;
	ogrenci* aranan_ogrenci = NULL;
	char kullanici_soyad[25];
	char kullanici_ogrenciNo[25];

	system("cls");
	cout << "Arama seceneklerinden birini seciniz...\n";
	cout << "Numaraya gore arama: N\n";
	cout << "Soyadina gore arama: S\n";

	cout << "Seciminizi giriniz: ";
	cin >> secim;

	system("cls");

	if (secim == 'N')
	{
		cout << "Aramak istediginiz ogrenci numarasini giriniz: ";
		cin >> kullanici_ogrenciNo;

		ogrenci* temp = ogrenciler;

		while (temp != NULL)
		{
			int sonuc = strcmp(temp->ogrno, kullanici_ogrenciNo);
			if (sonuc == 0)
			{
				aranan_ogrenci = temp;
				ogrenciBulundu = true;
				break;
			}
			temp = temp->sonraki;
		}
        if (!ogrenciBulundu)
			cout << kullanici_ogrenciNo << " nolu ogrenci bulunamadi...\n";
	}
	else if (secim == 'S')
	{
		cout << "Aramak istediginiz ogrenci soyadini giriniz: ";
		cin >> kullanici_soyad;

		ogrenci* temp = ogrenciler;

		while (temp != NULL)
		{
			int sonuc = strcmp(temp->soyad, kullanici_soyad);
			if (sonuc == 0)
			{
				aranan_ogrenci = temp;
				ogrenciBulundu = true;
				break;
			}
			temp = temp->sonraki;
		}
	}
	else
	{
		cout << "Gecersiz input...\n";
		return;
	}
    if (!ogrenciBulundu)
		cout << kullanici_ogrenciNo << " nolu ogrenci bulunamadi...\n";
	else
	{
		if (aranan_ogrenci != NULL)
		{
			cout << "Ogrenci bulundu...\n";
			cout << aranan_ogrenci->ogrno << " " << aranan_ogrenci->ad << " " << aranan_ogrenci->soyad << ": ";
			ders* tempDers = aranan_ogrenci->dersdugumu;

			while (tempDers != NULL)
			{
				cout << tempDers->derskodu << " " << tempDers->dersadi << " - ";
				tempDers = tempDers->sonraki;
			}
		}
	}
}
void kesisimBul()
{
	char dersKod1[25];
	char dersKod2[25];

	cout << "Birinci ders kodunu giriniz: ";
	cin >> dersKod1;
	cout << "Ikinci ders kodunu giriniz: ";
	cin >> dersKod2;

	ogrenci* temp = ogrenciler;

	cout << "Iki dersi alan kesisim ogrencileri: \n";

	while (temp != NULL)
	{
		bool ders1 = false;
		bool ders2 = false;

		ders* tempDers = temp->dersdugumu;
		while (tempDers != NULL)
		{
			if (!ders1)
			{
				int sonuc = strcmp(tempDers->derskodu, dersKod1);
				if (sonuc == 0)
				{
					ders1 = true;
				}
			}
			else if (!ders2)
			{
				int sonuc = strcmp(tempDers->derskodu, dersKod2);
				if (sonuc == 0)
				{
					ders2 = true;
				}
			}
			tempDers = tempDers->sonraki;
		}
		if (ders1 && ders2)
		{
			cout << temp->ogrno << " " << temp->ad << " " << temp->soyad << endl;
		}
		temp = temp->sonraki;
	}

}

void dosyayaYaz()
{
	ofstream dosya("output.txt", ios::out);
	ogrenci* tempOgrenci = ogrenciler;
	ders* tempDers = NULL;
	while (tempOgrenci != NULL)
	{
		dosya << tempOgrenci->ogrno << " " << tempOgrenci->ad << " " << tempOgrenci->soyad << " ";
		tempDers = tempOgrenci->dersdugumu;
		while (tempDers != NULL)
		{
			dosya << tempDers->derskodu << " " << tempDers->dersadi << "   ";
			tempDers = tempDers->sonraki;
		}
		tempOgrenci = tempOgrenci->sonraki;
	}
	dosya.close();
	cout << "Dosya yazildi.\n";
	delete tempOgrenci;
	delete tempDers;
}

void Menu()
{
	system("cls");
	cout << "\t\t--- ISLEM MENUSU ---\n";
	cout << "Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz...\n";
	cout << "Arama yapmak icin: A\n";
	cout << "Ders silmek icin: D\n";
	cout << "Kesisim bulmak icin: K\n";
	cout << "Listeye ekrana yazdirmak icin: L\n";
	cout << "Ogrenci silmek icin: O\n";
	cout << "Dosyaya yaz: Y\n";
	cout << "Cikis icin: C\n";
}

int main()
{
	char secim;
	string dosyaAdi;
	dosyaAdi = "mat101.txt";
	listeKur(dosyaAdi);
	dosyaAdi = "fiz101.txt";
	listeKur(dosyaAdi);
	dosyaAdi = "eng101.txt";
	listeKur(dosyaAdi);

	do
	{
		Menu();
		cout << "Seciminizi giriniz: ";
		cin >> secim;

		switch (secim)
		{
		case 'A': // Arama yapma
			system("cls");
			ara();
			system("pause");
			break;
		case 'D': // Ders silme
			system("cls");
			dersSil();
			system("pause");
			break;
		case 'K': // Kesisim bulma
			system("cls");
			kesisimBul();
			system("pause");
			break;
		case 'L': // Listeyi ekrana yazdirma
			system("cls");
			listele();
			system("pause");
			break;
		case 'O': // Ogrenci silme
			system("cls");
			ogrenciSil();
			system("pause");
			break;
		case 'Y': // Dosyaya yazma
			system("cls");
			dosyayaYaz();
			system("pause");
			break;
		}
	}
	while (secim != 'C');

	return 0;
}
