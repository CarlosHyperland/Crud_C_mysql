#include <iostream>
#include <regex>
#include "Estudiante.h"

using namespace std;

int main() {

	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;

	int opcion = 0;

	do {

		cout << "\n========== MENU CRUD ==========" << endl;
		cout << "1. Crear Estudiante" << endl;
		cout << "2. Mostrar Estudiantes" << endl;
		cout << "3. Actualizar Estudiante" << endl;
		cout << "4. Eliminar Estudiante" << endl;
		cout << "5. Salir" << endl;

		cout << "Seleccione una opcion: ";

		if (!(cin >> opcion)) {

			cout << "\nError: Debe ingresar solo opciones numericas del menu." << endl;

			cin.clear();
			cin.ignore(1000, '\n');

			opcion = 0;
			continue;
		}

		cin.ignore();

		switch (opcion) {

		case 1: {

			cout << "\n===== CREAR ESTUDIANTE =====" << endl;

			// VALIDACION CODIGO

			bool codigo_valido = false;

			do {

				cout << "Ingrese Codigo: ";
				cin >> codigo;
				cin.ignore();

				if (codigo.empty()) {

					cout << "Error: El codigo es obligatorio." << endl;
				}
				else if (codigo.length() > 4) {

					cout << "Error: El codigo solo puede tener 4 caracteres." << endl;
				}
				else {

					regex formato_codigo("^E[0-9]{3}$");

					if (!regex_match(codigo, formato_codigo)) {

						cout << "Error: Formato invalido. Ejemplo: E001" << endl;
					}
					else {

						// VALIDAR CODIGO DUPLICADO

						ConexionBD cn;

						cn.abrir_conexion();

						if (cn.getConector()) {

							string consulta =
								"SELECT codigo FROM estudiantes WHERE codigo = '" + codigo + "';";

							const char* c = consulta.c_str();

							int q_estado = mysql_query(cn.getConector(), c);

							if (!q_estado) {

								MYSQL_RES* resultado;
								MYSQL_ROW fila;

								resultado = mysql_store_result(cn.getConector());

								fila = mysql_fetch_row(resultado);

								if (fila) {

									cout << "Error: El codigo ya existe." << endl;
								}
								else {

									codigo_valido = true;
								}

								mysql_free_result(resultado);
							}
						}

						cn.cerrar_conexion();
					}
				}

			} while (!codigo_valido);

			cout << "Ingrese Nombres: ";
			getline(cin, nombres);

			cout << "Ingrese Apellidos: ";
			getline(cin, apellidos);

			cout << "Ingrese Direccion: ";
			getline(cin, direccion);

			cout << "Ingrese Telefono: ";
			cin >> telefono;
			cin.ignore();

			cout << "Ingrese Fecha Nacimiento: ";
			getline(cin, fecha_nacimiento);

			cout << "Ingrese Tipo Sangre: ";
			cin >> id_tipo_sangre;

			Estudiante e = Estudiante(
				nombres,
				apellidos,
				direccion,
				telefono,
				fecha_nacimiento,
				id_tipo_sangre,
				codigo,
				0
			);

			e.crear();

			break;
		}

		case 2: {

			cout << "\n===== LISTA ESTUDIANTES =====" << endl;

			Estudiante e;
			e.leer();

			break;
		}

		case 3: {

			cout << "\n===== ACTUALIZAR ESTUDIANTE =====" << endl;

			cout << "Ingrese ID a Modificar: ";
			cin >> id_estudiante;
			cin.ignore();

			// VALIDACION CODIGO

			bool codigo_valido = false;

			do {

				cout << "Ingrese Codigo: ";
				cin >> codigo;
				cin.ignore();

				if (codigo.empty()) {

					cout << "Error: El codigo es obligatorio." << endl;
				}
				else if (codigo.length() > 4) {

					cout << "Error: El codigo solo puede tener 4 caracteres." << endl;
				}
				else {

					regex formato_codigo("^E[0-9]{3}$");

					if (!regex_match(codigo, formato_codigo)) {

						cout << "Error: Formato invalido. Ejemplo: E001" << endl;
					}
					else {

						// VALIDAR CODIGO DUPLICADO

						ConexionBD cn;

						cn.abrir_conexion();

						if (cn.getConector()) {

							string consulta =
								"SELECT codigo FROM estudiantes WHERE codigo = '" + codigo +
								"' AND id_estudiante != " + to_string(id_estudiante) + ";";

							const char* c = consulta.c_str();

							int q_estado = mysql_query(cn.getConector(), c);

							if (!q_estado) {

								MYSQL_RES* resultado;
								MYSQL_ROW fila;

								resultado = mysql_store_result(cn.getConector());

								fila = mysql_fetch_row(resultado);

								if (fila) {

									cout << "Error: El codigo ya existe." << endl;
								}
								else {

									codigo_valido = true;
								}

								mysql_free_result(resultado);
							}
						}

						cn.cerrar_conexion();
					}
				}

			} while (!codigo_valido);

			cout << "Ingrese Nombres: ";
			getline(cin, nombres);

			cout << "Ingrese Apellidos: ";
			getline(cin, apellidos);

			cout << "Ingrese Direccion: ";
			getline(cin, direccion);

			cout << "Ingrese Telefono: ";
			cin >> telefono;
			cin.ignore();

			cout << "Ingrese Fecha Nacimiento: ";
			getline(cin, fecha_nacimiento);

			cout << "Ingrese Tipo Sangre: ";
			cin >> id_tipo_sangre;

			Estudiante e;

			e.setId_Estudiante(id_estudiante);
			e.setCodigo(codigo);
			e.setNombres(nombres);
			e.setApellidos(apellidos);
			e.setDireccion(direccion);
			e.setTelefono(telefono);
			e.setFecha_Nacimiento(fecha_nacimiento);
			e.setId_tipo_Sangre(id_tipo_sangre);

			e.actualizar();

			break;
		}

		case 4: {

			cout << "\n===== ELIMINAR ESTUDIANTE =====" << endl;

			cout << "Ingrese ID a Eliminar: ";
			cin >> id_estudiante;

			Estudiante e;

			e.setId_Estudiante(id_estudiante);

			e.borrar();

			break;
		}

		case 5:

			cout << "\nSaliendo del sistema..." << endl;
			break;

		default:

			cout << "\nError: Debe seleccionar una opcion valida del menu." << endl;
			break;
		}

	} while (opcion != 5);

	return 0;
}