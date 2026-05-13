#ifndef CINEMAMODELS_H
#define CINEMAMODELS_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>

class Film {
private:
    std::string titlu;
    bool este3D;
    double pretBaza;
public:
    Film(std::string t, bool e3d, double p) : titlu(t), este3D(e3d), pretBaza(p) {}
    std::string getTitlu() const { return titlu; }
    bool getEste3D() const { return este3D; }
    double getPretBaza() const { return pretBaza; }
};

class Sala {
private:
    int id;
    int randuri;
    int coloane;
    std::vector<std::vector<int>> locuri;

public:
    Sala(int _id, int _r, int _c) : id(_id), randuri(_r), coloane(_c) {
        locuri.resize(randuri, std::vector<int>(coloane, 0));
    }

    int getId() const { return id; }

    void ocupaLoc(int r, int l) {
        if (r >= 0 && r < randuri && l >= 0 && l < coloane) {
            if (locuri[r][l] == 1) throw std::runtime_error("Locul este deja ocupat!");
            locuri[r][l] = 1;
        }
        else {
            throw std::runtime_error("Indexul randului sau al locului este invalid!");
        }
    }

    void afiseazaHarta() const {
        std::cout << "\n      ========= ECRAN =========\n\n";

        // Numerotare coloane
        std::cout << "      ";
        for (int j = 1; j <= coloane; ++j) {
            std::cout << std::setw(3) << j;
        }
        std::cout << "\n      ";
        for (int j = 0; j < coloane * 3; ++j) std::cout << "-";
        std::cout << "\n";

        // Afisare randuri
        for (int i = 0; i < randuri; ++i) {
            std::cout << "R" << std::setw(2) << i + 1 << " |";
            for (int j = 0; j < coloane; ++j) {
                if (locuri[i][j] == 0)
                    std::cout << std::setw(3) << "O";
                else
                    std::cout << std::setw(3) << "X";
            }
            std::cout << " |\n";
        }

        std::cout << "      ";
        for (int j = 0; j < coloane * 3; ++j) std::cout << "-";
        std::cout << "\n      (O = Liber, X = Ocupat)\n";
    }
};

class Rezervare {
protected:
    Film film;
    int rand;
    int loc;
    double pretFinal;
public:
    Rezervare(Film f, int r, int l, double p) : film(f), rand(r), loc(l), pretFinal(p) {}
    virtual void afiseazaDetalii() const {
        std::cout << "Film: " << film.getTitlu() << " | Loc: R" << rand + 1 << " L" << loc + 1 << " | Pret: " << pretFinal << " RON\n";
    }
    virtual ~Rezervare() {}
};

class RezervareOnline : public Rezervare {
private:
    std::string email;
public:
    RezervareOnline(Film f, int r, int l, double p, std::string e) : Rezervare(f, r, l, p), email(e) {}
    void afiseazaDetalii() const override {
        std::cout << "[ONLINE] ";
        Rezervare::afiseazaDetalii();
        std::cout << "Confirmare trimisa la: " << email << "\n";
    }
};

class ICinemaService {
public:
    virtual void adaugaFilm(Film f) = 0;
    virtual void adaugaSala(Sala s) = 0;
    virtual void afiseazaFilme() = 0;
    virtual void afiseazaLocuri(int idSala) = 0;
    virtual void realizeazaRezervare(int idSala, int r, int l, std::string titlu, std::string email) = 0;
    virtual ~ICinemaService() {}
};

#endif