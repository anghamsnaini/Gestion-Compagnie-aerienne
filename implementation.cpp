#include "Classes.h"
#include"string"

//--------------------heures------------------------------
heures::heures(int h = 0, int m = 0, int s = 0)
{
	heure = h;
	minute = m;
	seconde = s;
}

heures::~heures(void)
{
}

void heures::affiche()
{
	cout << heure << ":" << minute << ":" << seconde << endl;
}

istream& operator>> (istream& in, heures& h)
{
	in >> h.heure >> h.minute >> h.seconde;
	return in;
}

ostream& operator<<(ostream& out, heures& h)
{
	out << h.heure << "\t" << h.minute << "\t" << h.seconde;
	return out;
}
//------------------------date:----------------------------

date::date(int j = 0, int m = 0, int a = 0)
{
	jour = j;
	mois = m;
	annee = a;
}
date::~date(void)
{
}
void date::saisie()
{
	cout << "donnez le jour" << endl;
	cin >> jour;
	cout << "Donnez le mois" << endl;
	cin >> mois;
	cout << "donnez l'annee" << endl;
	cin >> annee;
}
void date::affiche()
{
	cout << jour << "/" << mois << "/" << annee << endl;
}
istream& operator>> (istream& in, date& d)
{
	in >> d.jour >> d.mois >> d.annee;
	return in;
}
ostream& operator<<(ostream& out, date& d)
{
	out << d.jour << "\t" << d.mois << "\t" << d.annee;
	return out;
}
bool operator==(date& d1, date& d2)
{
	if (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour == d2.jour)
		return true;
	else
		return false;
}
//-----------------------------personne:--------------------------------
personne::personne(int i = 0, string n = "", string p = "", char s = ' ', string nat = "", int j = 0, int m = 0, int a = 0, int phone = 0, string mail = "") :dateNaissance(j, m, a)
{
	id = i;
	nom = n;
	prenom = p;
	sexe = s;
	nationalite = nat;
	telephone = phone;
	email = mail;
}
personne::~personne()
{
}
void personne::affiche()
{
	cout << "id: " << id << endl;
	cout << "le nom: " << nom << endl;
	cout << "le prenom: " << prenom << endl;
	cout << "le sexe: " << sexe << endl;
	cout << "la nationalite: " << nationalite << endl;
	cout << "La date de naissance: ";
	dateNaissance.affiche();
	cout << "le numero de telephone: " << telephone << endl;
	cout << "email: " << email << endl;
	cout << endl;
}
void personne::saisie()
{
	cout << "Donnez votre numero d'id: " << endl;
	cin >> id;
	cout << "Donnez votre nom: " << endl;
	cin >> nom;
	cout << "Donnez votre prenom: " << endl;
	cin >> prenom;
	do
	{
		cout << "Donnez le sexe: ";
		cout << "h:homme / f:femme" << endl;
		cin >> sexe;
	} while (sexe != 'h' && sexe != 'f');
	cout << "Donnez votre nationalité: " << endl;
	cin >> nationalite;
	cout << "Donnez votre date de naissance: " << endl;
	dateNaissance.date::saisie();
	cout << "Donnez votre numero de telephone: " << endl;
	cin >> telephone;
	cout << "Donnez votre email: " << endl;
	cin >> email;
}
ostream& operator<<(ostream& out, personne& p)
{
	out << p.id << "\t" << p.nom << "\t" << p.prenom << "\t" << p.sexe << "\t" << p.nationalite << "\t" << p.telephone << "\t" << p.email;
	out << "\t" << p.dateNaissance.get_jour() << "\t" << p.dateNaissance.get_mois() << "\t" << p.dateNaissance.get_annee();
	return out;
}
istream& operator>> (istream& in, personne& p)
{
	in >> p.id >> p.nom >> p.prenom >> p.sexe >> p.nationalite >> p.telephone >> p.email >> p.dateNaissance;
	return in;
}
void personne::consulte_vol(int id_trajet)
{
	int j = 1;
	vector<vol>tab;
	vol v;
	ifstream f("vols.txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> v;
			tab.push_back(v);
			i++;
		}
	}
	else
		cout << "impossible d'ouvrir le fichier" << endl;
	for (unsigned int i = 0; i < tab.size(); i++)
		if (tab[i].get_etat() == "ouvert")
		{
			if (tab[i].get_tajet().id == id_trajet)
			{
				cout << "\n vol numero " << j << " : \n" << endl;
				tab[i].affiche_vol();
				j++;
			}
		}
}

//-----------------------------passager:----------------------------------

passager::passager(int i = 0, string n = "", string p = "", char s = ' ', string nat = "", int j = 0, int m = 0, int a = 0, int phone = 0, string mail = "", int pass = 0)
	:personne(i, n, p, s, nat, j, m, a, phone, mail)
{
	num_passeport = pass;
	nbre_vols_reserves = num_vols_reserves.size();
}
passager::~passager()
{}
void passager::saisie()
{
	personne::saisie();
	cout << "Donnez votre numero du passeport: " << endl;
	cin >> num_passeport;
}
void passager::affiche()
{
	personne::affiche();
	cout << "Numero du passeport: " << num_passeport << endl;
	cout << "Nombre des vols reserves: " << nbre_vols_reserves << endl;
	cout << "Numero de vols reserves: " << endl;
	for (unsigned int i = 0; i < num_vols_reserves.size(); i++)
		cout << num_vols_reserves[i] << endl;
}
ostream& operator<<(ostream& out, passager& p)
{
	out << p.id << "\t" << p.nom << "\t" << p.prenom << "\t" << p.sexe << "\t" << p.nationalite << "\t" << p.telephone;
	out << "\t" << p.email << "\t" << p.dateNaissance.get_jour() << "\t" << p.dateNaissance.get_mois() << "\t";
	out << p.dateNaissance.get_annee() << "\t" << p.num_passeport << "\t" << p.nbre_vols_reserves;
	for (unsigned int i = 0; i < p.num_vols_reserves.size(); i++)
		out << "\t" << p.num_vols_reserves[i];
	out << "\n";
	return out;
}
istream& operator>>(istream& in, passager& p)
{
	int x;
	in >> p.id >> p.nom >> p.prenom >> p.sexe >> p.nationalite >> p.telephone >> p.email;
	in >> p.dateNaissance >> p.num_passeport >> p.nbre_vols_reserves;
	for (int i = 0; i < p.nbre_vols_reserves; i++)
	{
		in >> x;
		p.num_vols_reserves.push_back(x);
	}
	return in;
}
bool passager::exist_sur_vol(date d)
{
	vol v;
	vector<int> t;
	//chercher dans le fichier vols.txt les num de vols dont possede la date d et l'ajouter à t:
	ifstream f("vols.txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> v;
			if (v.get_date_depart().get_jour()==d.get_jour() && v.get_date_depart().get_mois()==d.get_mois() && v.get_date_depart().get_annee()==d.get_annee())
				t.push_back(v.get_id());
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier vols.txt " << endl;
	//chercher dans les fichier de vols l'existance du passager:
	for (unsigned int i = 0; i < t.size(); i++)
		if (this->exist_sur_vol(t[i]) != -1)
			return true;
	return false;
}
int passager::exist_sur_vol(int num)
{
	vector<passager>t;
	passager p;
	string s = to_string(num);
	ifstream f(s + ".txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> p;
			t.push_back(p);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier " << s << ".txt" << endl;
	unsigned int i = 0;
	bool test = false;
	while (test == false && i < t.size())
	{
		if (t[i].num_passeport == this->num_passeport)
			test = true;
		i++;
	}
	i--;
	if (test)
		return i;
	else
		return -1;
}
bool passager::reservation(vol v)
{
	cout << exist_sur_vol(v.get_id()) << endl;
	if (this->exist_sur_vol(v.get_id()) == -1)
	{
		if (!(this->exist_sur_vol(v.get_date_depart())))
		{
			num_vols_reserves.push_back(v.get_id());
			nbre_vols_reserves += 1;
			this->ajout_ds_fichier(v.get_id());
			v.set_nb_places_reserve(v.get_nb_places_reserve() + 1);
			v.MAJ_etat();
			//Metre àjour le fichier "vols.txt" 
			v.supprime_du_fichier();
			v.ajout_au_fichier();
		}
		else
			return false;
	}
	else
		return false;
	return true;
}
void passager::ajout_ds_fichier(int num)
{
	string s = to_string(num);
	fstream f(s + ".txt", ios::out | ios::in | ios::app);
	if (f)
	{
		f << *this;
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier" << s << ".txt" << endl;
}
void passager::supprimer_du_fichier(int num)
{
	vector<passager>t;
	passager p;
	string s = to_string(num);
	ifstream f(s + ".txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> p;
			t.push_back(p);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier" << s << ".txt" << endl;
	unsigned int i = 0;
	bool test = false;
	while (test == false && i < t.size())
	{
		if (t[i].num_passeport == this->num_passeport)
			test = true;
		i++;
	}
	i--;
	if (test)
	{
		t.erase(t.begin() + i);
		ofstream f1(s + ".txt", ios::out | ios::trunc);
		if (f1)
		{
			f1 << t.size() << "\n";
			for (unsigned int i = 0; i < t.size(); i++)
				f1 << t[i];
			f1.close();
		}
		else
			cout << "impossible d'ouvrir le fichier" << s << ".txt" << endl;
	}
	else
		cout << "passager non existant" << endl;
}

//-----------------------------trajet:----------------------------------

trajet::trajet(int id , double p , string e , int nb )
{
	this->id = id;
	this->prix = p;
	this->etat = e;
	this->nb_escales = nb;
}
trajet::trajet()
{
	id = 0;
	prix = 0;
	etat = "";
	nb_escales = 0;
}
trajet::~trajet()
{
}
void trajet::saisie()
{
	cout << "Donnez l'id du trajet: " << endl;
	cin >> id;
	string x;
	int test = 1;
	while (test == 1)
	{
		cout << "Donnez une ville: " << endl;
		cin >> x;
		escales.push_back(x);
		do
		{
			cout << "voulez vous ajouter autres ville?" << endl;
			cout << "1->oui \n 2->non " << endl;
			cin >> test;
		} while (test != 1 && test != 2);
	}
	cout << "Donnez le prix: " << endl;
	cin >> prix;
	do
	{
		cout << "Donnez l'etat du trajet:(ouvert/ferme) " << endl;
		cin >> etat;
	} while (etat != "ferme" && etat != "ouvert");
	nb_escales = escales.size();
}
void trajet::fermer_trajet()
{
	etat = "ferme";
}

void trajet::ouvrir_trajet()
{
	etat = "ouvert";
}

ostream& operator<<(ostream& out, trajet& t)
{
	out << t.id << "\t";
	out << t.nb_escales << "\t";
	for (unsigned int i = 0; i < t.escales.size(); i++)
		out << t.escales[i] << "\t";
	out << t.prix << "\t" << t.etat;
	return out;
}
istream& operator>>(istream& in, trajet& t)
{
	in >> t.id >> t.nb_escales;
	string x;
	for (int i = 0; i < t.nb_escales; i++)
	{
		in >> x;
		t.escales.push_back(x);
	}
	in >> t.prix >> t.etat;
	return in;
}
void trajet::affiche_trajet()
{
	cout << "id du trajet: " << id << endl;
	cout << "depart : " << escales[0] << endl;
	cout << "nombre d'escales: " << nb_escales - 2 << endl;
	cout << "escale(s): " << endl;
	if (nb_escales - 2 == 0)
		for (int i = 1; i < nb_escales - 1; i++)
		{
			cout << escales[i] << endl;
		}
	cout << "arrivee : " << escales[escales.size() - 1] << endl;
}
void trajet::ajout_ds_fichier()
{
	fstream f;
	f.open("tajet.txt", ios::in | ios::out | ios::app);
	if (f)
	{
		f << *this;
		f << "\n";
	}
	else
		cout << "impossible d'ouvrir le fichier trajet.txt" << endl;
}
//--------------------Vol:------------------------------//
vol::vol(int id, int a1, int m1, int j1, int a2, int m2, int j2, int h1, int mn1, int s1, int h2, int mn2, int s2, int c, string e,
	int nb, int id_trajet, double pr, string e_trajet, int nb_es) :date_depart(a1, m1, j1), date_arrivee(a2, m2, j2), heure_depart(h1, mn1, s1),
	heure_arrivee(h2, mn2, s2)

{
	this->id = id;
	capacité = c;
	etat = e;
	nb_place_reserve = nb;
	trajet t(id_trajet, pr, e_trajet, nb_es);
}
vol::vol()
{
	id = 0;
	capacité = 0;
	etat = "";
	nb_place_reserve = 0;
}
vol::~vol()
{
}
void vol::affiche_vol()
{
	cout << "ID" << id << endl;
	cout << "date de depart : ";
	this->date_depart.affiche();
	cout << "date arrivée : " << endl;
	this->date_arrivee.affiche();
	cout << "heure de depart : " << endl;
	this->heure_depart.affiche();
	this->heure_arrivee.affiche();
	cout << "Trajet:" << endl;
	t.affiche_trajet();
	cout << "Capacite:" << capacité << endl;
	cout << "nb place reserves:" << nb_place_reserve << endl;
	cout << "etat:" << etat << endl;
}
void vol::MAJ_etat()
{
	if (nb_place_reserve == capacité)
		etat = "fermé";
}
void vol::saisie()
{
	int a, j, m, h, mn, s, a1, j1, m1, h1, mn1, s1;
	cout << "donner l'id du vol:" << endl;
	cin >> id;
	t.saisie();
	cout << "donner la date de depart" << endl;
	date_depart.saisie();
	cout << "donner la date d''arrivee" << endl;
	date_arrivee.saisie();
	cout << "donner l'heure de depart" << endl;
	cin >> h >> mn >> s;
	heures heu(h, mn, s);
	heure_depart = heu;
	cout << "donner l'heure d''arivee" << endl;
	cin >> h1 >> mn1 >> s1;
	heures heu1(h1, mn1, s1);
	heure_arrivee = heu1;
	nb_place_reserve = 0;
	cout << "donner la capacite de ce vol ";
	cin >> capacité;
	etat = "ouvert";
}
heures vol::calcul_duree()
{
	int de_sec = (heure_depart.get_seconde()) + (heure_depart.get_minute() * 60) + (heure_depart.get_heure() * 3600);
	int ar_sec = (heure_arrivee.get_seconde()) + (heure_arrivee.get_minute() * 60) + (heure_arrivee.get_heure() * 3600);
	int difference = ar_sec - de_sec;
	heures h(difference / 3600, ((difference % 3600) / 60), ((difference % 3600) % 60));
	return h;
}
ostream& operator<<(ostream& out, vol& v)
{
	out << v.id << "\t" << v.t << "\t" << v.date_depart << "\t" << v.date_arrivee << "\t" << v.heure_depart << "\t" << v.heure_arrivee << "\t" << v.nb_place_reserve << "\t" << v.capacité << "\t" << v.etat << "\n";
	return out;
}
istream& operator>>(istream& in, vol& v)
{
	in >> v.id >> v.t >> v.date_depart >> v.date_arrivee >> v.heure_depart >> v.heure_arrivee >> v.nb_place_reserve >> v.capacité >> v.etat;
	return in;
}
void vol::supprime_du_fichier()
{
	vector<vol> tab;
	ifstream f("vols.txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			vol v;
			f >> v;
			tab.push_back(v);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier vols.txt" << endl;
	unsigned int i = 0;
	bool test = false;
	while (test == false && i < tab.size())
	{
		if (tab[i].id == this->id)
			test = true;
		i++;
	}
	i--;
	if (test)
	{
		tab.erase(tab.begin() + i);
		ofstream f1("vols.txt", ios::out | ios::trunc);
		if (f1)
		{
			f1 << tab.size() << "\n";
			for (unsigned  int i = 0; i < tab.size() - 1; i++)
				f1 << tab[i];
			f1.close();
		}
		else
			cout << "impossible d'ouvrir le fichier vols.txt" << endl;
	}
	else
		cout << "vol non existant" << endl;
}
void vol::ajout_au_fichier()
{
	ofstream f("vols.txt", ios::out | ios::app);
	if (f)
	{
		f << *this;
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier" << endl;
}
//----------------Compagnie:--------------------------------

compagnie::compagnie()
{
}
compagnie::~compagnie()
{
}
void compagnie::ajout_destination()
{
	string dest;
	cout << "donner la destination a ajouter" << endl;
	cin >> dest;
	this->tab_destination.push_back(dest);
}
bool operator== (trajet t1, trajet t2)
{
	unsigned int i = 0;
	bool b = true;
	while ((i < t1.escales.size()) && (t1.escales[i] == t2.escales[i]) && (b == true)) { i += 1; }
	if ((t1.escales[i] == t2.escales[i]) || ( i > t1.escales.size())) { b = false; }
	return b;
}
void compagnie::supprimer_trajet(trajet t)
{
	for (unsigned int i = 0; i < tab_trajet.size(); i++)
		if (tab_trajet[i] == t)
			tab_trajet.erase(tab_trajet.begin() + i);
}
bool compagnie::existe_destination(string destination)
{
	for (unsigned int i = 0; i < tab_destination.size(); i++)
	{
		if (destination == tab_destination[i])
			return true;
		else
			return false;
	}
}
void compagnie::consulte_trajetspossible(string)
{
	for (unsigned int i = 0; i < tab_trajet.size(); i++)
		tab_trajet[i].affiche_trajet();
}
void   compagnie::afficher_fichier_vols()
{
	vol v;
	ifstream f("vols.txt", ios::in);
	if (f)
	{
		int j = 1;
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> v;
			cout << "\n vol numero " << j << " : \n" << endl;
			j++;
			v.affiche_vol();
			i++;
		}
	}
	else
		cout << "impossible d'ouvrir le fichier vols.txt" << endl;
}
void compagnie::supprimer_trajet(int id_trajet)
{
	vector<trajet> tab;
	ifstream f("tajet.txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			trajet t;
			f >> t;
			tab.push_back(t);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier vols.txt" << endl;
	unsigned int i = 0;
	bool test = false;
	while (test == false && i < tab.size())
	{
		if (tab[i].id == id_trajet)
			test = true;
		i++;
	}
	i--;
	if (test)
	{
		tab.erase(tab.begin() + i);
		ofstream f1("tajet.txt", ios::out | ios::trunc);
		if (f1)
		{
			f1 << tab.size() << "\n";
			for (i = 0; i < tab.size(); i++)
				f1 << tab[i];
			f1.close();
		}
		else
			cout << "impossible d'ouvrir le fichier vols.txt" << endl;
	}
	else
		cout << "vol non existant" << endl;
}
void compagnie::consult_passagers_vol(int id_vol)
{
	vector<passager>t;
	passager p;
	string s = to_string(id_vol);
	ifstream f(s + ".txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> p;
			t.push_back(p);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier" << s << ".txt" << endl;
	for (int j = 0; j < t.size(); j++)
	{
		cout << "\n Passager " << j + 1 << ": \n" << endl;;
		t[j].affiche();
	}
}

//-------------------------------------------------------------

vol recherche_vol(int num)
{
	vector<vol> tab;
	vol v;
	ifstream f("vols.txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> v;
			tab.push_back(v);
			i++;
		}
		f.close();
	}
	else
		cout << "impossible d'ouvrir le fichier" << endl;
	int i = 0;
	while (i < tab.size())
	{
		if (tab[i].get_id() == num)
			return tab[i];
		i++;
	}
	cout << "vol innexistant" << endl;
	vol v1;
	return v1;
}
passager recherche_passager(int id_passager, int id_vol)
{
	vector<passager> tab;
	passager p;
	string s = to_string(id_vol);
	ifstream f(s + ".txt", ios::in);
	if (f)
	{
		string x;
		f.seekg(0, ios::beg);
		getline(f, x);
		stringstream geek(x);
		int n = 0;
		geek >> n;
		int i = 0;
		while (i < n)
		{
			f >> p;
			tab.push_back(p);
			i++;
		}
		f.close();
	}
	else
		cout <<  "impossible d'ouvrir le fichier" << endl;
	int i = 0;
	while (i < tab.size())
	{
		if (tab[i].get_id() == id_passager)
			return tab[i];
		i++;
	}
	cout << "Passager innexistant" << endl;
	passager p1;
	return p1;
}
//--------------------------------------------------------------------------------------

void main()
{
	compagnie cmp;
	passager p;
	bool tester;
	int rep, rep1, rep3, rep4, rep5;
	int id_vol;
	string rep2;
	vol v;
	int choix, id_pas;
	bool test = true;
	while (test == true)
	{
		do
		{
			cout << ("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb") << endl;
			cout << ("\n               \xba                        MENU:                                        \xba") << endl;
			cout << ("\n               \xba    1 : pour connecter en tant qu'un client                          \xba") << endl;
			cout << ("\n               \xba    2 : pour connecter en tant qu'une compagnie                      \xba") << endl;
			cout << ("\n               \xba                                                                     \xba") << endl;
			cout << ("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc") << endl;
			cout << ("\n\n                                Votre choix  :  ");
			cin >> rep;
		} while (rep != 1 && rep != 2);
		if (rep == 1)
		{
			p.saisie();
			do
			{
				cout << ("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb") << endl;
				cout << ("\n               \xba                                                                             \xba") << endl;
				cout << ("\n               \xba    1 -> Consulter les vols trajet possibles pour votre destination          \xba") << endl;
				cout << ("\n               \xba    2 -> Reserver                                                            \xba") << endl;
				cout << ("\n               \xba                                                                             \xba") << endl;
				cout << ("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc") << endl;
				cout << ("\n\n                                Votre choix  :  ");
				cin >> rep1;
			} while (rep1 != 1 && rep1 != 2);
			if (rep1 == 1)
			{
				do
				{
					cout << "entrez votre destination souhaitee" << endl;
					cin >> rep2;
					tester = cmp.existe_destination(rep2);
					if (tester == false)
						cout << "La destination que vous avez demande n'existe pas" << endl;
				} while (tester != true);
				cmp.consulte_trajetspossible(rep2);
				cout << "Entrez l'id du trajet souhaitee" << endl;
				cin >> rep4;
				p.consulte_vol(rep4);
				do
				{
					cout << "voulez vous reserve?" << endl;
					cout << "1 : oui" << endl;
					cout << "2 : non" << endl;
					cout << "Entrez votre choix: " << endl;
					cin >> rep5;
				} while (rep5 != 1 && rep5 != 2);
				if (rep5 == 1)
				{
					cout << "Donnez l'id du vol a reserver" << endl;
					cin >> id_vol;
					vol v = recherche_vol(id_vol);
					bool test_res = p.reservation(v);
					if (test_res == true)
						cout << "Reservation effectuer" << endl;
					else
						cout << "Reservation Impossible" << endl;
				}
			}
			else
			{
				cmp.afficher_fichier_vols();
				cout << " \n Donnez l'id du vol a reserver:" << endl;
				cin >> id_vol;
				vol v = recherche_vol(id_vol);
				bool test_res = p.reservation(v);
				if (test_res == true)
					cout << "Reservation effectuer" << endl;
				else
					cout << "Reservation Impossible" << endl;
			}
		}
		else
		{
			do
			{
				cout << ("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb") << endl;
				cout << ("\n               \xba                                                                     \xba") << endl;
				cout << ("\n               \xba    1 : Ajout d'une nouvelle destination                             \xba") << endl;
				cout << ("\n               \xba    2 : Supprimer un trajet                                          \xba") << endl;
				cout << ("\n               \xba    3 : Afficher la liste des vols disponible                 \xba") << endl;
				cout << ("\n               \xba    4 : Recherche un passager                                        \xba") << endl;
				cout << ("\n               \xba    5 : Ajouter un passager                                          \xba") << endl;
				cout << ("\n               \xba    6 : Supprimer un passager                                        \xba") << endl;
				cout << ("\n               \xba                                                                     \xba") << endl;
				cout << ("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc") << endl;
				cout << ("\n\n                                Votre choix  :  ");
				cin >> rep3;
			} while (rep3 != 1 && rep3 != 2 && rep3 != 3 && rep3 != 4 && rep3 != 5 && rep3 != 6);
			switch (rep3)
			{
			case 1: cmp.ajout_destination(); break;
			case 2:
			{	int id_t;
			cout << "Donnez id du trajet a supprimer" << endl;
			cin >> id_t;
			cmp.supprimer_trajet(id_t); break;
			}
			case 3:
			{	cmp.afficher_fichier_vols();
			cout << "\nDonnez l'id du vol dont vous voulez consulter: " << endl;
			cin >> id_vol;
			cmp.consult_passagers_vol(id_vol);
			break;
			}
			case 4:
			{	cout << "Donner le num vol dont vous souhaitez chercher le passager: " << endl;
			cin >> id_vol;
			cout << "Donnez l'id du passager dont vous voulez rechercher: " << endl;
			cin >> id_pas;
			p = recherche_passager(id_pas, id_vol);
			cout << "\n Id du passager recherche: " << endl;
			p.affiche();
			break;
			}
			case 5:
			{	cout << "Donnez les donnees du passager a ajouter: \n" << endl;
			p.saisie();
			cout << "Donnez le numero de vol pour lui ajouter un passager" << endl;
			cin >> id_vol;
			p.ajout_ds_fichier(id_vol);
			break;
			}
			case 6:
			{	cout << "Donnez l'id du passager dont vous voulez supprimer: " << endl;
			cin >> id_pas;
			cout << "Donnez le numero de vol pour lui supprimer un passager" << endl;
			cin >> id_vol;
			p = recherche_passager(id_pas, id_vol);
			p.supprimer_du_fichier(id_vol);
			break;
			}
			}
		}
		do
		{
			cout << ("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb") << endl;
			cout << ("\n               \xba                                                                     \xba") << endl;
			cout << ("\n               \xba    1 -> Retour au menu                                              \xba") << endl;
			cout << ("\n               \xba    2 -> Quitter                                                     \xba") << endl;
			cout << ("\n               \xba                                                                     \xba") << endl;
			cout << ("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc") << endl;
			cout << ("\n\n                                Votre choix  :  ");
			cin >> choix;
		} while (choix != 1 && choix != 2);
		switch (choix)
		{
		case 1:test = true; break;
		case 2:test = false; break;
		}
	}
	system("PAUSE");
}






