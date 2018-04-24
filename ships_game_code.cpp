#include <cstdlib>
#include <string>
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;








typedef struct node Node;

struct node
{
	int wsp_x;
	int wsp_y;
	Node *next;
	Node *prev;
};

class Lista
{

public:

	Node *head;
	Node *tail;
	Node *current;

public:

	Lista(Node*h = NULL, Node*t = NULL, Node*c = NULL)
	{
		head = h;
		tail = t;
		current = c;
	}



	Node *createzero()
	{
		Node *nev;
		nev = new (Node);
		nev->wsp_x = 0;
		nev->wsp_y = 0;
		nev->next = NULL;
		nev->prev = NULL;

		return nev;
	}



	void addlastzero()
	{
		Node *tmp = createzero();

		if (head == NULL)
			head = tmp;
		else {
			Node *pom = head;
			while (pom->next != NULL)
				pom = pom->next;
			pom->next = tmp;
			tmp->prev = pom;
		}

		tail = tmp;
	}



	void deletecurrent()
	{
		if (current == head && current == tail) {
			head = NULL;
			tail = NULL;
		}
		else if (current == head) {
			head = (current->next);
			(current->next)->prev = NULL;
		}
		else if (current == tail) {
			tail = (current->prev);
			(current->prev)->next = NULL;
		}
		else {
			(current->next)->prev = (current->prev);
			(current->prev)->next = (current->next);
		}

		delete current;
	}



	void deletehead()
	{
		Node *pom = head;

		head = (pom->next);
		(pom->next)->prev = NULL;

		delete pom;
	}



	void moveleft()
	{
		current = current->prev;
	}



	void moveright()
	{
		current = current->next;
	}


	void deleteall()
	{
		if (head == NULL);
		else
		{
			Node *pom = head;
			Node *tmp;
			while (pom->next != NULL)
			{
				tmp = pom;
				pom = (pom->next);
				delete tmp;
			}
			delete pom;
			head = NULL;
			tail = NULL;
			current = NULL;
		}
	}



	void showall()
	{
		if (head == NULL)
			cout << "EMPTY!!!";
		else
		{
			Node *pom = head;
			while (pom->next != NULL)
			{
				cout << pom->wsp_x;
				cout << pom->wsp_y;
				cout << " ";
				pom = pom->next;
			}
			cout << pom->wsp_x;
			cout << pom->wsp_y;
		}
	}



	int countall()
	{
		int i;
		if (head == NULL)
			i = 0;
		else
		{
			Node *pom = head;
			i = 1;
			while (pom->next != NULL)
			{
				i++;
				pom = pom->next;
			}
		}
		return i;
	}


	~Lista()
	{
		deleteall();
	}

};










class Plansza
{

public:

	Lista *statki;
	int ilosc_pol;
	int bok_m;
	int bok_n;
	int stat2;
	int stat3;
	int stat4;
	int stat5;
	char plan[10002][28];

public:

	Plansza(Lista *s1, int ipol=0, int m=0, int n=0, int s2=0, int s3=0, int s4=0, int s5=0)
	{
		statki = s1;
		ilosc_pol = ipol;
		bok_m = m;
		bok_n = n;
		stat2 = s2;
		stat3 = s3;
		stat4 = s4;
		stat5 = s5;
	}

	void zeruj_plansze()
	{
		int i, j;
		for (i = 0; i < 10002; i++)
			for (j = 0; j < 28; j++)
				plan[i][j] = NULL;
		stat2 = 0;
		stat3 = 0;
		stat4 = 0;
		stat5 = 0;
	}

	void wczytaj_plansze()
	{
		cout << "Podaj ilosc wierszy (1-10000): ";
		cin >> bok_m;
		cout << endl << "Podaj ilosc kolumn (A-Z): ";
		char pom;
		cin >> pom;
		bok_n = ((int) pom) - 64;

		int i, j;
		for (i = 1; i <= bok_m; i++)
			for (j = 1; j <= bok_n; j++)
				plan[i][j] = '*';

		cout << endl << "Podaj ilosc statkow 2 masztowych: ";
		cin >> stat2;
		cout << endl << "Podaj ilosc statkow 3 masztowych: ";
		cin >> stat3;
		cout << endl << "Podaj ilosc statkow 4 masztowych: ";
		cin >> stat4;
		cout << endl << "Podaj ilosc statkow 5 masztowych: ";
		cin >> stat5;
		cout << endl;
	}

	void wczytaj_pobocznie()
	{
		int i, j;
		for (i = 1; i <= bok_m; i++)
			for (j = 1; j <= bok_n; j++)
				plan[i][j] = '*';
	}

	int sprwadz_kolizje(int maszt, int wersja, int pole_m, int pole_n)
	{
		if (wersja == 0)
		{
			if (pole_n + maszt - 1 > bok_n)
				return 0;

			int i, j;
			for (i=pole_m-1; i<=pole_m+2; i++)
				for (j = pole_n - 1; j <= pole_n + maszt; j++)
				{
					if (plan[i][j] == '*' || plan[i][j] == NULL);
					else return 0;
				}
		}
		else if (wersja == 1)
		{
			if (pole_m + maszt - 1 > bok_m)
				return 0;

			int i, j;
			for (i = pole_m - 1; i <= pole_m + maszt; i++)
				for (j = pole_n - 1; j <= pole_n + 2; j++)
				{
					if (plan[i][j] == '*' || plan[i][j] == NULL);
					else return 0;
				}
		}
		return 1;
	}

	void umiesc_statek(int maszt, int wersja, int pole_m, int pole_n)
	{
		if (wersja == 0)
		{
			int i, j;
			for (j = pole_n; j <= pole_n + maszt - 1; j++)
				plan[pole_m][j] = (char)(maszt + 48);
		}
		else if (wersja == 1)
		{
			int i, j;
			for (i = pole_m; i <= pole_m + maszt - 1; i++)
				plan[i][pole_n] = (char)(maszt + 48);
		}
	}

	int rozmiesc_statki()
	{
		int i, j;
		for (i = 1; i <= stat2; i++)
		{
			cout << "Statek 2 masztowy nr " << i << ". Pokazac aktualna plansze (0-nie, 1-tak) ? ";
			int pokaz;
			cin >> pokaz;
			if (pokaz == 1) pokaz_plansze_cheat();

			cout << endl << "Wersja wstawienia (0-poziom w prawo, 1-pion w dol, 2-powrot do parametrow): ";
			int wersja;
			cin >> wersja;
			if (wersja == 2) return 1;
			cout << endl << "Podaj wiersz pola wstawienia (1-" << bok_m << "): ";
			int pole_m;
			cin >> pole_m;
			cout << endl << "Podaj kolumne pola wstawienia (A-" << (char)(bok_n + 64) << "): ";
			char pom;
			cin >> pom;
			int pole_n = ((int)pom) - 64;

			j = sprwadz_kolizje(2, wersja, pole_m, pole_n);
			if (j == 0)
			{
				i--;
				cout << endl << "KOLIZJA!!! Sprobuj jeszcze raz." << endl << endl;
			}
			else
			{
				umiesc_statek(2, wersja, pole_m, pole_n);
				cout << endl << "WSTAWIONY!!!" << endl << endl;
			}
		}
		for (i = 1; i <= stat3; i++)
		{
			cout << endl << "Statek 3 masztowy nr " << i << ". Pokazac aktualna plansze (0-nie, 1-tak) ? ";
			int pokaz;
			cin >> pokaz;
			if (pokaz == 1) pokaz_plansze_cheat();

			cout << endl << "Wersja wstawienia (0-poziom w prawo, 1-pion w dol, 2-powrot do parametrow): ";
			int wersja;
			cin >> wersja;
			if (wersja == 2) return 1;
			cout << endl << "Podaj wiersz pola wstawienia (1-" << bok_m << "): ";
			int pole_m;
			cin >> pole_m;
			cout << endl << "Podaj kolumne pola wstawienia (A-" << (char)(bok_n + 64) << "): ";
			char pom;
			cin >> pom;
			int pole_n = ((int)pom) - 64;

			j = sprwadz_kolizje(3, wersja, pole_m, pole_n);
			if (j == 0)
			{
				i--;
				cout << endl << "KOLIZJA!!! Sprobuj jeszcze raz." << endl << endl;
			}
			else
			{
				umiesc_statek(3, wersja, pole_m, pole_n);
				cout << endl << "WSTAWIONY!!!" << endl << endl;
			}
		}
		for (i = 1; i <= stat4; i++)
		{
			cout << endl << "Statek 4 masztowy nr " << i << ". Pokazac aktualna plansze (0-nie, 1-tak) ? ";
			int pokaz;
			cin >> pokaz;
			if (pokaz == 1) pokaz_plansze_cheat();

			cout << endl << "Wersja wstawienia (0-poziom w prawo, 1-pion w dol, 2-powrot do parametrow): ";
			int wersja;
			cin >> wersja;
			if (wersja == 2) return 1;
			cout << endl << "Podaj wiersz pola wstawienia (1-" << bok_m << "): ";
			int pole_m;
			cin >> pole_m;
			cout << endl << "Podaj kolumne pola wstawienia (A-" << (char)(bok_n + 64) << "): ";
			char pom;
			cin >> pom;
			int pole_n = ((int)pom) - 64;

			j = sprwadz_kolizje(4, wersja, pole_m, pole_n);
			if (j == 0)
			{
				i--;
				cout << endl << "KOLIZJA!!! Sprobuj jeszcze raz." << endl << endl;
			}
			else
			{
				umiesc_statek(4, wersja, pole_m, pole_n);
				cout << endl << "WSTAWIONY!!!" << endl << endl;
			}
		}
		for (i = 1; i <= stat5; i++)
		{
			cout << endl << "Statek 5 masztowy nr " << i << ". Pokazac aktualna plansze (0-nie, 1-tak) ? ";
			int pokaz;
			cin >> pokaz;
			if (pokaz == 1) pokaz_plansze_cheat();

			cout << endl << "Wersja wstawienia (0-poziom w prawo, 1-pion w dol, 2-powrot do parametrow): ";
			int wersja;
			cin >> wersja;
			if (wersja == 2) return 1;
			cout << endl << "Podaj wiersz pola wstawienia (1-" << bok_m << "): ";
			int pole_m;
			cin >> pole_m;
			cout << endl << "Podaj kolumne pola wstawienia (A-" << (char)(bok_n + 64) << "): ";
			char pom;
			cin >> pom;
			int pole_n = ((int)pom) - 64;

			j = sprwadz_kolizje(5, wersja, pole_m, pole_n);
			if (j == 0)
			{
				i--;
				cout << endl << "KOLIZJA!!! Sprobuj jeszcze raz." << endl << endl;
			}
			else
			{
				umiesc_statek(5, wersja, pole_m, pole_n);
				cout << endl << "WSTAWIONY!!!" << endl << endl;
			}
		}
		int tech = 0;
		cout << endl << "Wcisnij 1 aby kontynuowac: ";
		cin >> tech;
		return 0;
	}





	void zeruj_statki()
	{
		(*statki).deleteall();
		ilosc_pol = 0;
	}

	void wczytaj_wszystkie_pola()
	{
		int i, j;
		for (i = 1; i <= bok_m; i++)
		{
			for (j = 1; j <= bok_n; j++)
			{
				(*statki).addlastzero();
				(*statki).tail->wsp_x = i;
				(*statki).tail->wsp_y = j;
			}
		}
		ilosc_pol = bok_m * bok_n;
	}





	int rozmiesc_statki_losowo()
	{
		srand(time(NULL));
		zeruj_statki();
		wczytaj_wszystkie_pola();
		int i, j;

		for (i = 1; i <= stat5; i++)
		{
			if ((*statki).head == NULL) return 1;

			int n = (rand() % ilosc_pol);
			ilosc_pol--;
			(*statki).current = (*statki).head;
			while (n > 0)
			{
				(*statki).moveright();
				n--;
			}

			int pole_m = (*statki).current->wsp_x;
			int pole_n = (*statki).current->wsp_y;
			char pom;
			pom = (char)(pole_n + 64);

			(*statki).deletecurrent();

			int wersja = (rand() % 2);

			j = sprwadz_kolizje(5, wersja, pole_m, pole_n);
			if (j == 0)
			{
				j = sprwadz_kolizje(5, ((wersja + 1) % 2), pole_m, pole_n);
				if (j == 0) i--;
				else
				{
					umiesc_statek(5, ((wersja+1)%2), pole_m, pole_n);
					zeruj_statki();
					wczytaj_wszystkie_pola();
				}
			}	
			else
			{
				umiesc_statek(5, wersja, pole_m, pole_n);
				zeruj_statki();
				wczytaj_wszystkie_pola();
			}
		}

		for (i = 1; i <= stat4; i++)
		{
			if ((*statki).head == NULL) return 1;

			int n = (rand() % ilosc_pol);
			ilosc_pol--;
			(*statki).current = (*statki).head;
			while (n > 0)
			{
				(*statki).moveright();
				n--;
			}

			int pole_m = (*statki).current->wsp_x;
			int pole_n = (*statki).current->wsp_y;
			char pom;
			pom = (char)(pole_n + 64);

			(*statki).deletecurrent();

			int wersja = (rand() % 2);

			j = sprwadz_kolizje(4, wersja, pole_m, pole_n);
			if (j == 0)
			{
				j = sprwadz_kolizje(4, ((wersja + 1) % 2), pole_m, pole_n);
				if (j == 0) i--;
				else
				{
					umiesc_statek(4, ((wersja + 1) % 2), pole_m, pole_n);
					zeruj_statki();
					wczytaj_wszystkie_pola();
				}
			}
			else
			{
				umiesc_statek(4, wersja, pole_m, pole_n);
				zeruj_statki();
				wczytaj_wszystkie_pola();
			}
		}

		for (i = 1; i <= stat3; i++)
		{
			if ((*statki).head == NULL) return 1;

			int n = (rand() % ilosc_pol);
			ilosc_pol--;
			(*statki).current = (*statki).head;
			while (n > 0)
			{
				(*statki).moveright();
				n--;
			}

			int pole_m = (*statki).current->wsp_x;
			int pole_n = (*statki).current->wsp_y;
			char pom;
			pom = (char)(pole_n + 64);

			(*statki).deletecurrent();

			int wersja = (rand() % 2);

			j = sprwadz_kolizje(3, wersja, pole_m, pole_n);
			if (j == 0)
			{
				j = sprwadz_kolizje(3, ((wersja + 1) % 2), pole_m, pole_n);
				if (j == 0) i--;
				else
				{
					umiesc_statek(3, ((wersja + 1) % 2), pole_m, pole_n);
					zeruj_statki();
					wczytaj_wszystkie_pola();
				}
			}
			else
			{
				umiesc_statek(3, wersja, pole_m, pole_n);
				zeruj_statki();
				wczytaj_wszystkie_pola();
			}
		}

		for (i = 1; i <= stat2; i++)
		{
			if ((*statki).head == NULL) return 1;

			int n = (rand() % ilosc_pol);
			ilosc_pol--;
			(*statki).current = (*statki).head;
			while (n > 0)
			{
				(*statki).moveright();
				n--;
			}

			int pole_m = (*statki).current->wsp_x;
			int pole_n = (*statki).current->wsp_y;
			char pom;
			pom = (char)(pole_n + 64);

			(*statki).deletecurrent();

			int wersja = (rand() % 2);

			j = sprwadz_kolizje(2, wersja, pole_m, pole_n);
			if (j == 0)
			{
				j = sprwadz_kolizje(2, ((wersja + 1) % 2), pole_m, pole_n);
				if (j == 0) i--;
				else
				{
					umiesc_statek(2, ((wersja + 1) % 2), pole_m, pole_n);
					zeruj_statki();
					wczytaj_wszystkie_pola();
				}
			}
			else
			{
				umiesc_statek(2, wersja, pole_m, pole_n);
				zeruj_statki();
				wczytaj_wszystkie_pola();
			}
		}
		
		return 0;
	}

	void pokaz_plansze()
	{
		int i, j;
		cout << endl << " " << "\t";
		for (j = 1; j <= bok_n; j++)
			cout << (char)(j + 64) << " ";
		cout << endl << endl;

		for (i = 1; i <= bok_m; i++)
		{
			cout << i << "\t";
			for (j = 1; j <= bok_n; j++)
			{
				if (plan[i][j] == 'x' || plan[i][j] == 'o' || plan[i][j] == 'z')
					cout << plan[i][j] << " ";
				else cout << "*" << " ";
			}
			cout << endl;
		}

		cout << endl;
	}

	void pokaz_plansze_cheat()
	{
		int i, j;
		cout << endl << " " << "\t";
		for (j = 1; j <= bok_n; j++)
			cout << (char)(j + 64) << " ";
		cout << endl << endl;

		for (i = 1; i <= bok_m; i++)
		{
			cout << i << "\t";
			for (j = 1; j <= bok_n; j++)
			{
				if (plan[i][j] != 'o' && plan[i][j] != '*')
					cout << plan[i][j] << " ";
				else cout << " " << " ";
			}
			cout << endl;
		}

		cout << endl;
	}

	int sprawdz_plansze()
	{
		int i, j;
		for (i = 1; i <= bok_m; i++)
			for (j = 1; j <= bok_n; j++)
			{
				if (plan[i][j] == 'o' || plan[i][j] == '*' || plan[i][j] == 'x' || plan[i][j] == 'z');
				else return 0;
			}
		return 1;
	}

	int sprawdz_czy_zatopiony(int x, int y)
	{
		int i, j;
		char test;
		test = plan[x][y];
		for (i = x+1, j = y; plan[i][j] != '*' && plan[i][j] != 'o' && plan[i][j] != NULL; i++)
		{
			if (plan[i][j] == 'x');
			else if (plan[i][j] == test) return 0;
		}
		for (i = x-1, j = y; plan[i][j] != '*' && plan[i][j] != 'o' && plan[i][j] != NULL; i--)
		{
			if (plan[i][j] == 'x');
			else if (plan[i][j] == test) return 0;
		}
		for (i = x, j = y+1; plan[i][j] != '*' && plan[i][j] != 'o' && plan[i][j] != NULL; j++)
		{
			if (plan[i][j] == 'x');
			else if (plan[i][j] == test) return 0;
		}
		for (i = x, j = y-1; plan[i][j] != '*' && plan[i][j] != 'o' && plan[i][j] != NULL; j--)
		{
			if (plan[i][j] == 'x');
			else if (plan[i][j] == test) return 0;
		}
		return 1;
	}

	void zatop_statek(int x, int y)
	{
		int i, j;
		for (i = x + 1, j = y; plan[i][j] == 'x'; i++) plan[i][j] = 'z';
		for (i = x - 1, j = y; plan[i][j] == 'x'; i--) plan[i][j] = 'z';
		for (i = x, j = y + 1; plan[i][j] == 'x'; j++) plan[i][j] = 'z';
		for (i = x, j = y - 1; plan[i][j] == 'x'; j--) plan[i][j] = 'z';
		plan[x][y] = 'z';
	}

	
};




class Gracz
{
public:

	Lista *strzaly;
	Plansza *moja;
	Plansza *przeciwnik;
	int sprawdz;
	int ilosc_pocz;
	int ilosc_akt;

	Gracz(Lista *l1,  Plansza *p1, Plansza *p2, int s = 0, int ip = 0, int ia = 0)
	{
		strzaly = l1;
		moja = p1;
		przeciwnik = p2;
		sprawdz = s;
		ilosc_pocz = ip;
		ilosc_akt = ia;
	}









	void zeruj_strzaly()
	{
		(*strzaly).deleteall();
		ilosc_pocz = 0;
		ilosc_akt = 0;
	}

	void wczytaj_wszystkie_strzaly()
	{
		int i, j;
		for (i = 1; i <= (*moja).bok_m; i++)
		{
			for (j = 1; j <= (*moja).bok_n; j++)
			{
				(*strzaly).addlastzero();
				(*strzaly).tail->wsp_x = i;
				(*strzaly).tail->wsp_y = j;
			}
		}
		ilosc_pocz = (*moja).bok_m * (*moja).bok_n;
		ilosc_akt = ilosc_pocz;
	}











	void wykonaj_strzal(int ponow)
	{
		if (ponow == 1) cout << endl << "TO JUZ BYLO ALBO PRZESADZILES!!! Sprobuj jeszcze raz." << endl;

		int cheat;
		cout << endl << "OSZUKUJESZ ??? (0-nie, 1-tak) : ";
		cin >> cheat;
		if (cheat == 0)
			(*przeciwnik).pokaz_plansze();
		else
			(*przeciwnik).pokaz_plansze_cheat();

		cout << "Podaj wspolrzedne strzalu.";
		cout << endl << "Podaj wiersz pola strzalu (1-" << (*przeciwnik).bok_m << "): ";
		int x;
		cin >> x;
		cout << "Podaj kolumne pola strzalu (A-" << (char)((*przeciwnik).bok_n + 64) << "): ";
		char pom;
		cin >> pom;
		int y = ((int)pom) - 64;

		if ((*przeciwnik).plan[x][y] == 'o' || (*przeciwnik).plan[x][y] == 'x' || (*przeciwnik).plan[x][y] == 'z' || (*przeciwnik).plan[x][y] == NULL)
		{
			wykonaj_strzal(1);
		}
		else if ((*przeciwnik).plan[x][y] == '*')
		{
			cout << endl << "PUDLO!!!" << endl << endl;
			(*przeciwnik).plan[x][y] = 'o';
		}
		else
		{
			int z = (*przeciwnik).sprawdz_czy_zatopiony(x, y);
			if (z == 0)
			{
				(*przeciwnik).plan[x][y] = 'x';
				cout << endl << "TRAFIONY!!!" << endl << endl;
			}
			else if (z == 1)
			{
				(*przeciwnik).zatop_statek(x, y);
				cout << endl << "TRAFIONY ZATOPIONY!!!" << endl << endl;
			}
		}
	}

	void wykonaj_strzal_losowo(int ponow)
	{
		srand(time(NULL));
		int cheat;
		cout << endl << "PODGLADASZ ??? (0-nie, 1-tak) : ";
		cin >> cheat;
		if (cheat == 0)
			(*przeciwnik).pokaz_plansze();
		else
			(*przeciwnik).pokaz_plansze_cheat();


		int n = (rand() % ilosc_akt);
		ilosc_akt--;
		(*strzaly).current = (*strzaly).head;
		while (n > 0)
		{
			(*strzaly).moveright();
			n--;
		}

		int x = (*strzaly).current->wsp_x;
		int y = (*strzaly).current->wsp_y;
		char pom;
		pom = (char)(y + 64);

		(*strzaly).deletecurrent();

		cout << "Wspolrzedne strzalu: ";
		cout << x << " " << pom << endl;

		/*if ((*przeciwnik).plan[x][y] == 'o' || (*przeciwnik).plan[x][y] == 'x' || (*przeciwnik).plan[x][y] == 'z')
		{
			wykonaj_strzal_losowo(1);
		}
		else*/ if ((*przeciwnik).plan[x][y] == '*')
		{
			cout << endl << "PUDLO!!!" << endl << endl;
			(*przeciwnik).plan[x][y] = 'o';
		}
		else
		{
			int z = (*przeciwnik).sprawdz_czy_zatopiony(x, y);
			if (z == 0)
			{
				(*przeciwnik).plan[x][y] = 'x';
				cout << endl << "TRAFIONY!!!" << endl << endl;
			}
			else if (z == 1)
			{
				(*przeciwnik).zatop_statek(x, y);
				cout << endl << "TRAFIONY ZATOPIONY!!!" << endl << endl;
			}
		}
	}

	void sprawdz_czy_wygrales()
	{
		sprawdz = (*przeciwnik).sprawdz_plansze();
	}

};




class Menu
{
public:

	Lista *lista1;
	Lista *lista2;
	Plansza *plan1;
	Plansza *plan2;
	Gracz *gracz1;
	Gracz *gracz2;
	int tryb;
	int akcja;
	int koniec;

	Menu(Lista *l1, Lista *l2, Plansza *p1, Plansza *p2, Gracz *g1, Gracz *g2, int t = 0, int a = 0, int k = 1)
	{
		lista1 = l1;
		lista2 = l2;
		plan1 = p1;
		plan2 = p2;
		gracz1 = g1;
		gracz2 = g2;
		tryb = t;
		akcja = a;
		koniec = k;
	}

	void menu_poczatkowe()
	{
		system("cls");
		cout << "GRA W STATKI" << endl << endl;
		cout << "1 - nowa gra" << endl;
		cout << "0 - koniec" << endl;
		cout << "Co chcesz zrobic? ";
		cin >> koniec;
		if (koniec == 0);
		else koordynator();
	}

	void koordynator()
	{
		system("cls");
		cout << "Wczytywanie parametrow plansz." << endl << endl;
		(*plan1).zeruj_plansze();
		(*plan2).zeruj_plansze();
		(*plan1).wczytaj_plansze();
		(*plan2).bok_m = (*plan1).bok_m;
		(*plan2).bok_n = (*plan1).bok_n;
		(*plan2).stat2 = (*plan1).stat2;
		(*plan2).stat3 = (*plan1).stat3;
		(*plan2).stat4 = (*plan1).stat4;
		(*plan2).stat5 = (*plan1).stat5;
		(*plan2).wczytaj_pobocznie();
		(*gracz1).zeruj_strzaly();
		(*gracz2).zeruj_strzaly();
		(*gracz1).wczytaj_wszystkie_strzaly();
		(*gracz2).wczytaj_wszystkie_strzaly();

		system("cls");
		cout << "Wczytywanie trybu graczy." << endl << endl;
		cout << "Jaki tryb gry wybierasz? (1-pl_vs_kom, 2-pl_vs_pl, 3-kom_vs_kom): ";
		cin >> tryb;
		if (tryb == 1) pl_vs_kom();
		else if (tryb == 2) pl_vs_pl();
		else if (tryb == 3) kom_vs_kom();
	}

	void pl_vs_kom()
	{
		system("cls");
		cout << "Wczytywanie Twoich statkow." << endl << endl;
		cout << "Jak wczytac statki (1-recznie, 2-automatycznie): ";
		cin >> akcja;

		system("cls");
		int blad = 0;
		if (akcja == 1) blad = (*plan1).rozmiesc_statki();
		else if (akcja == 2) blad = (*plan1).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "TWOJ BLAD!!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}

		system("cls");
		cout << "Twoje rozmieszczenie statkow." << endl;
		(*plan1).pokaz_plansze_cheat();
		cout << "Wcisnij 1 aby kontynuowac: ";
		cin >> akcja;

		system("cls");
		blad = (*plan2).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "BLAD PRZECIWNIKA!!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}
		cout << "Twoj przeciwnik rozmiescil swoje statki." << endl << endl;
		cout << "Wcisnij 1 aby kontynuowac: ";
		cin >> akcja;

		akcja = 0;
		while (akcja == 0)
		{
			system("cls");
			cout << "Twoj ruch. Wykonaj strzal." << endl;
			(*gracz1).wykonaj_strzal(0);
			cout << "Wcisnij 1 aby kontynuowac lub 2 aby wrocic do menu glownego: ";
			cin >> akcja;
			if (akcja == 2) menu_poczatkowe();
			else
			{
				(*gracz1).sprawdz_czy_wygrales();
				if ((*gracz1).sprawdz == 1) akcja = 1;
				else
				{
					akcja = 0;

					system("cls");
					cout << "Ruch przeciwnika. Wykonuje strzal." << endl;
					(*gracz2).wykonaj_strzal_losowo(0);
					cout << "Twoj przeciwnik wykonal strzal." << endl << endl;
					cout << "Wcisnij 1 aby kontynuowac: ";
					cin >> akcja;
					(*gracz2).sprawdz_czy_wygrales();
					if ((*gracz2).sprawdz == 1) akcja = 2;
					else akcja = 0;
				}
			}
		}

		if (koniec == 0);
		else
		{
			system("cls");
			if (akcja == 1) cout << "GRATULACJE, WYGRALES!!!";
			else if (akcja == 2) cout << "NIESTETY PRZEGRALES!!!";
			cout << endl << endl << "Wcisnij 1 aby wrocic do menu glownego: ";
			cin >> akcja;
			menu_poczatkowe();
		}
	}




	void pl_vs_pl()
	{
		system("cls");
		cout << "Wczytywanie statkow Gracza nr 1." << endl << endl;
		cout << "Jak wczytac statki (1-recznie, 2-automatycznie): ";
		cin >> akcja;

		system("cls");
		int blad = 0;
		if (akcja == 1) blad = (*plan1).rozmiesc_statki();
		else if (akcja == 2) blad = (*plan1).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "BLAD GRACZA NR 1 !!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}

		system("cls");
		cout << "Rozmieszczenie statkow Gracza nr 1." << endl;
		(*plan1).pokaz_plansze_cheat();
		cout << "Wcisnij 1 aby przejsc do Gracza nr 2: ";
		cin >> akcja;

		system("cls");
		cout << "Wczytywanie statkow Gracza nr 2." << endl << endl;
		cout << "Jak wczytac statki (1-recznie, 2-automatycznie): ";
		cin >> akcja;

		system("cls");
		if (akcja == 1) blad = (*plan2).rozmiesc_statki();
		else if (akcja == 2) blad = (*plan2).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "BLAD GRACZA NR 2 !!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}

		system("cls");
		cout << "Rozmieszczenie statkow Gracza nr 2." << endl;
		(*plan2).pokaz_plansze_cheat();
		cout << "Wcisnij 1 aby przejsc do rozgrywki: ";
		cin >> akcja;

		akcja = 0;
		while (akcja == 0)
		{
			system("cls");
			cout << "Ruch Gracza nr 1. Wykonaj strzal." << endl;
			(*gracz1).wykonaj_strzal(0);
			cout << "Wcisnij 1 aby kontynuowac lub 2 aby wrocic do menu glownego: ";
			cin >> akcja;
			if (akcja == 2) menu_poczatkowe();
			else
			{
				(*gracz1).sprawdz_czy_wygrales();
				if ((*gracz1).sprawdz == 1) akcja = 1;
				else
				{
					akcja = 0;

					system("cls");
					cout << "Ruch Gracza nr 2. Wykonaj strzal." << endl;
					(*gracz2).wykonaj_strzal(0);
					cout << "Wcisnij 1 aby kontynuowac lub 2 aby wrocic do menu glownego: ";
					cin >> akcja;
					if (akcja == 2) menu_poczatkowe();
					else
					{
						(*gracz2).sprawdz_czy_wygrales();
						if ((*gracz2).sprawdz == 1) akcja = 2;
						else akcja = 0;
					}
				}
			}
		}

		if (koniec == 0);
		else
		{
			system("cls");
			if (akcja == 1) cout << "GRATULACJE, WYGRAL GRACZ NR 1 !!!";
			else if (akcja == 2) cout << "GRATULACJE, WYGRAL GRACZ NR 2 !!!";
			cout << endl << endl << "Wcisnij 1 aby wrocic do menu glownego: ";
			cin >> akcja;
			menu_poczatkowe();
		}
	}




	void kom_vs_kom()
	{
		system("cls");
		int blad = 0;
		blad = (*plan1).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "BLAD GRACZA NR 1 !!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}
		cout << "Gracz nr 1 rozmiescil swoje statki." << endl;
		int cheat;
		cout << endl << "PODGLADASZ ??? (0-nie, 1-tak) : ";
		cin >> cheat;
		if (cheat == 0) cout << endl;
		else
			(*plan1).pokaz_plansze_cheat();
		cout << "Wcisnij 1 aby przejsc do Gracza nr 2: ";
		cin >> akcja;

		system("cls");
		blad = (*plan2).rozmiesc_statki_losowo();
		if (blad == 1)
		{
			system("cls");
			cout << "BLAD GRACZA NR 2 !!! Sprobuj jeszcze raz wczytac parametry." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac: ";
			cin >> akcja;
			koordynator();
		}
		cout << "Gracz nr 2 rozmiescil swoje statki." << endl;
		cheat;
		cout << endl << "PODGLADASZ ??? (0-nie, 1-tak) : ";
		cin >> cheat;
		if (cheat == 0) cout << endl;
		else
			(*plan2).pokaz_plansze_cheat();
		cout << "Wcisnij 1 aby przejsc do rozgrywki: ";
		cin >> akcja;

		akcja = 0;
		while (akcja == 0)
		{
			system("cls");
			cout << "Ruch Gracza nr 1. Wykonuje strzal." << endl;
			(*gracz1).wykonaj_strzal_losowo(0);
			cout << "Gracz nr 1 wykonal strzal." << endl << endl;
			cout << "Wcisnij 1 aby kontynuowac lub 2 aby wrocic do menu glownego: ";
			cin >> akcja;
			if (akcja == 2) menu_poczatkowe();
			else
			{
				(*gracz1).sprawdz_czy_wygrales();
				if ((*gracz1).sprawdz == 1) akcja = 1;
				else
				{
					akcja = 0;

					system("cls");
					cout << "Ruch Gracza nr 2. Wykonuje strzal." << endl;
					(*gracz2).wykonaj_strzal_losowo(0);
					cout << "Gracz nr 2 wykonal strzal." << endl << endl;
					cout << "Wcisnij 1 aby kontynuowac: ";
					cin >> akcja;
					(*gracz2).sprawdz_czy_wygrales();
					if ((*gracz2).sprawdz == 1) akcja = 2;
					else akcja = 0;
				}
			}
		}

		if (koniec == 0);
		else
		{
			system("cls");
			if (akcja == 1) cout << "WYGRAL GRACZ NR 1 !!!";
			else if (akcja == 2) cout << "WYGRAL GRACZ NR 2 !!!";
			cout << endl << endl << "Wcisnij 1 aby wrocic do menu glownego: ";
			cin >> akcja;
			menu_poczatkowe();
		}
	}



};




int main()
{
	Lista l1;
	Lista l2;

	Lista s1;
	Lista s2;

	Plansza p1(&s1);
	Plansza p2(&s2);

	Gracz g1(&l1, &p1, &p2);
	Gracz g2(&l2, &p2, &p1);

	Menu m(&l1, &l2, &p1, &p2, &g1, &g2);

	m.menu_poczatkowe();

	cout << endl << "KONIEC!!!" << endl << endl;


	system("pause");
	return 0;
}



