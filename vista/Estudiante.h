#pragma once
#include <iostream>
#include <string>


#include <mysql.h>

#include "Persona.h"
#include "ConexionBD.h"

using namespace std;

class Estudiante : public Persona {

    // ATRIBUTOS
private:
    string codigo;
    int id_estudiante;

    // CONSTRUCTORES
public:
    Estudiante() {
        id_estudiante = 0;
    }

    Estudiante(
        string nom,
        string ape,
        string dir,
        string tel,
        string fn,
        int id_ts,
        string cod,
        int id_e
    ) : Persona(nom, ape, dir, tel, fn, id_ts)
    {
        codigo = cod;
        id_estudiante = id_e;
    }

    // =========================
    // SETTERS
    // =========================

    void setId_Estudiante(int e) {
        id_estudiante = e;
    }

    void setCodigo(string c) {
        codigo = c;
    }

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

    int getId_estudiante() {
        return id_estudiante;
    }

    string getCodigo() {
        return codigo;
    }

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

    int getId_Tipo_Sangre() {
        return id_tipo_sangre;
    }

    // =========================
    // CREAR
    // =========================

    void crear() {

        int q_estado = 0;

        ConexionBD cn;

        cn.abrir_conexion();

        if (cn.getConector()) {

            string id_ts = to_string(id_tipo_sangre);

            string consulta =
                "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipo_sangre) VALUES ('" +
                codigo + "','" +
                nombres + "','" +
                apellidos + "','" +
                direccion + "','" +
                telefono + "','" +
                fecha_nacimiento + "'," +
                id_ts + ");";

            const char* c = consulta.c_str();

            q_estado = mysql_query(cn.getConector(), c);

            if (q_estado == 0) {
                cout << "Ingreso de dato exitoso" << endl;
            }
            else {
                cout << "Consulta fallida" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }

        cn.cerrar_conexion();
    }

    // =========================
    // LEER
    // =========================

    void leer() {

        int q_estado = 0;

        ConexionBD cn;

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        cn.abrir_conexion();

        if (cn.getConector()) {

            string consulta =
                "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, "
                "e.direccion, e.telefono, e.fecha_nacimiento, ts.sangre "
                "FROM estudiantes e "
                "INNER JOIN tipos_sangre ts "
                "ON e.id_tipo_sangre = ts.id_tipos_sangre;";

            const char* c = consulta.c_str();

            q_estado = mysql_query(cn.getConector(), c);

            if (q_estado == 0) {

                resultado = mysql_store_result(cn.getConector());

                while ((fila = mysql_fetch_row(resultado))) {

                    cout
                        << fila[0] << " | "
                        << fila[1] << " | "
                        << fila[2] << " | "
                        << fila[3] << " | "
                        << fila[4] << " | "
                        << fila[5] << " | "
                        << fila[6] << " | "
                        << fila[7] << endl;
                }
            }
            else {
                cout << "Error en consulta" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }

        cn.cerrar_conexion();
    }

    // =========================
    // ACTUALIZAR
    // =========================

    void actualizar() {

        int q_estado = 0;

        ConexionBD cn;

        cn.abrir_conexion();

        if (cn.getConector()) {

            string id_ts = to_string(id_tipo_sangre);
            string id_e = to_string(id_estudiante);

            string consulta =
                "UPDATE estudiantes SET "
                "codigo='" + codigo +
                "', nombres='" + nombres +
                "', apellidos='" + apellidos +
                "', direccion='" + direccion +
                "', telefono='" + telefono +
                "', fecha_nacimiento='" + fecha_nacimiento +
                "', id_tipo_sangre=" + id_ts +
                " WHERE id_estudiante=" + id_e + ";";

            const char* c = consulta.c_str();

            q_estado = mysql_query(cn.getConector(), c);

            if (q_estado == 0) {
                cout << "Actualizacion exitosa" << endl;
            }
            else {
                cout << "Consulta fallida" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }

        cn.cerrar_conexion();
    }

    // =========================
    // BORRAR
    // =========================

    void borrar() {

        int q_estado = 0;

        ConexionBD cn;

        cn.abrir_conexion();

        if (cn.getConector()) {

            string id_e = to_string(id_estudiante);

            string consulta =
                "DELETE FROM estudiantes WHERE id_estudiante = " + id_e + ";";

            const char* c = consulta.c_str();

            q_estado = mysql_query(cn.getConector(), c);

            if (q_estado == 0) {
                cout << "Eliminacion exitosa" << endl;
            }
            else {
                cout << "Consulta fallida" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }

        cn.cerrar_conexion();
    }
};