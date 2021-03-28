#pragma once
#include "string"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 
using namespace std;

class heures
{
	int heure, minute, seconde;
public:
	heures(int, int, int);
	~heures(void);
	int get_seconde() { return seconde; }
	int get_minute() { return minute; }
	int get_heure() { return heure; }
	void set_seconde(int s) { seconde = s; }
	void set_minute(int m) { minute = m; }
	void set_heure(int h) { heure = h; }
	void affiche();
	friend istream& operator>> (istream&, heures&);
	friend ostream& operator<<(ostream&, heures&);
};

class date
{
	int jour, mois, annee;
public:
	date(int, int, int);
	~date(void);
	int get_jour() { return jour; }
	int get_mois() { return mois; }
	int get_annee() { return annee; }
	void set_jour(int j) { jour = j; }
	void set_mois(int m) { mois = m; }
	void set_annee(int a) { annee = a; }
	void saisie();
	void affiche();
	friend istream& operator>> (istream&, date&);
	friend ostream& operator<<(ostream&, date&);
	friend bool operator==(date&, date&);
};



class personne
{
protected:
	int id, telephone;
	string nom, prenom, email, nationalite;
	char sexe;
	date dateNaissance;
public:
	personne(int, string, string, char, string, int, int, int, int, string);
	~personne();
	//Get && Set:
	int get_id() { return id; }
	int get_telephone() { return telephone; }
	string get_nom() { return nom; }
	string get_prenom() { return prenom; }
	string get_email() { return email; }
	string get_nationalite() { return nationalite; }
	char get_sexe() { return sexe; }
	date get_dateNaissance() { return dateNaissance; }
	void set_id(int id) { this->id = id; }
	void set_telephone(int telephone) { this->telephone = telephone; }
	void set_nom(string nom) { this->nom = nom; }
	void set_prenom(string prenom) { this->prenom = prenom; }
	void set_email(string email) { this->email = email; }
	void set_nationalite(string nationalite) { this->nationalite = nationalite; }
	void set_dateNaissance(date dateNaissance)
	{
		this->dateNaissance.set_jour(dateNaissance.get_jour());
		this->dateNaissance.set_mois(dateNaissance.get_mois());
		this->dateNaissance.set_annee(dateNaissance.get_annee());
	}
	//Methodes:
	void affiche();
	void saisie();
	friend ostream& operator<<(ostream&, personne&);
	friend istream& operator>>(istream&, personne&);
	void consulte_vol(int);//ouvrrir le fichier vols afficher les vols dont possede le trajet d'id donner en parametre
};

class trajet
{
public:
	int id;
	vector<string>escales;
	double prix;
	string etat;
	int nb_escales;
public:
	trajet();
	trajet(int, double, string, int);
	~trajet();
	void set_prix(double p) { prix = p; }
	double get_prix() { return prix; }
	void set_etat(string e) { etat = e; }
	string get_etat() { return etat; }
	void saisie();
	void ouvrir_trajet();
	void fermer_trajet();
	friend ostream& operator<<(ostream&, trajet&);
	friend istream& operator>>(istream&, trajet&);
	void affiche_trajet();
	void ajout_ds_fichier();
};

class vol
{
	int id;
	trajet t;
	date date_depart, date_arrivee;
	heures heure_depart, heure_arrivee;
	int nb_place_reserve, capacité;
	string etat;
	//vector<passager>tab_passager;
public:
	vol(int, int, int, int, int, int, int, int, int, int, int, int, int, int, string, int, int, double, string, int);
	~vol(void);
	vol();

	//Get && Set:
	int get_id() { return id; }
	date get_date_depart() { return date_depart; }
	date get_date_arrivee() { return date_arrivee; }
	int get_nb_places_reserve() { return nb_place_reserve; }
	int get_capacité() { return capacité; }
	string get_etat() { return etat; }
	trajet get_tajet() { return t; }
	heures get_heure_arrivee() { return heure_arrivee; }
	heures get_heure_depart() { return heure_depart; }

	void set_id(int id) { this->id = id; }
	void set_nb_places_reserve(int n) { nb_place_reserve = n; }

	//Methodes:
	void saisie();
	void affiche_vol();
	void MAJ_etat();
	void modifier_vol();
	heures calcul_duree();
	friend ostream& operator<<(ostream&, vol&);
	friend istream& operator>>(istream&, vol&);
	void supprime_du_fichier();
	void ajout_au_fichier();
};

class passager :public personne
{
protected:
	int num_passeport;
	int nbre_vols_reserves;
	vector<int>num_vols_reserves;
public:
	passager(int, string, string, char, string, int, int, int, int, string, int);
	~passager();
	//Get && Set:
	int get_num_passeport() { return num_passeport; }
	int get_nbre_vols_reserves() { return nbre_vols_reserves; }
	void set_num_passeport(int n) { num_passeport = n; }
	void set_nbre_vols_reserves(int n) { nbre_vols_reserves = n; }
	//Methodes:
	void saisie();
	void affiche();
	bool reservation(vol);//parametre: vol à reserver  
						  //&& retourne vrai si la reservation est possible
	bool exist_sur_vol(date);//tester l'existance du passager sur un vol à une date donnée
	int exist_sur_vol(int);//tester l'existance du passager sur le vol de l'id donner en parametre
						   //&& renvoi l'indice du passager s'il existe -1 sinon
	friend ostream& operator<<(ostream&, passager&);
	friend istream& operator>>(istream&, passager&);
	void ajout_ds_fichier(int);//prend comme parametre le numero de vol 
	void supprimer_du_fichier(int);//prend comme parametre le numero de vol 
	
};

class compagnie
{
	vector<trajet> tab_trajet;
	vector<string> tab_destination;
	//vector <passager> tab_passager;

public:
	compagnie();
	~compagnie();
	void ajout_destination();
	void supprimer_trajet(trajet);
	friend bool operator== (trajet, trajet);
	void affiche_passager(trajet);
	void ajout_vol();
	bool existe_destination(string);
	void consulte_trajetspossible(string);
	//void annuler_vol();
	friend ostream& operator<< (ostream& f, vector<string>);
	friend istream& operator>> (istream& f, vector<string>);
	friend ostream& operator<< (ostream& f, vector<trajet>);
	friend istream& operator>> (istream& f, vector<trajet>);
	static  void  creer(fstream& f);
	static void   afficher_fichier_vols();
	void supprimer_trajet(int);
	void consult_passagers_vol(int id_vol);
};

passager recherche_passager(int id_passager, int id_vol);
vol recherche_vol(int);//retourne le vol d'id donne en parametre
//(si le vol n'existe pas elle affiche "vol innexistant" et retourne un vol construit par defaut!!!