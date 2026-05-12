#pragma once
#include <iostream>
#include <string>

using namespace std;

class Persona {

    // ATRIBUTOS
protected:
    string nombres;
    string apellidos;
    string direccion;
    string telefono;
    string fecha_nacimiento;
    int id_tipo_sangre = 0;

    // CONSTRUCTORES
public:

    Persona() {
    }

    Persona(
        string nom,
        string ape,
        string dir,
        string tel,
        string fn,
        int id_ts
    ) {

        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        fecha_nacimiento = fn;
        id_tipo_sangre = id_ts;
    }

    // =========================
    // SETTERS
    // =========================

    void setNombres(string n) {
        nombres = n;
    }

    void setApellidos(string a) {
        apellidos = a;
    }

    void setDireccion(string d) {
        direccion = d;
    }

    void setTelefono(string t) {
        telefono = t;
    }

    void setFecha_Nacimiento(string f) {
        fecha_nacimiento = f;
    }

    void setId_tipo_Sangre(int ts) {
        id_tipo_sangre = ts;
    }

    // =========================
    // GETTERS
    // =========================

    string getNombres() {
        return nombres;
    }

    string getApellidos() {
        return apellidos;
    }

    string getDireccion() {
        return direccion;
    }

    string getTelefono() {
        return telefono;
    }

    string getFecha_Nacimiento() {
        return fecha_nacimiento;
    }

    int getId_tipo_Sangre() {
        return id_tipo_sangre;
    }
};
