#include <iostream>
#include <regex>
#include "Estudiante.h"
#include <ctime>

using namespace std;

int main() {

	string codigo, nombres, apellidos, direccion, fecha_nacimiento, telefono;
	int id_tipo_sangre = 0, id_estudiante = 0;

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

			// VALIDACION NOMBRES

			bool nombres_validos = false;

			do {

				cout << "Ingrese Nombres: ";
				getline(cin, nombres);

				if (nombres.empty()) {

					cout << "Error: El nombre es obligatorio." << endl;
				}
				else if (nombres.length() > 60) {

					cout << "Error: El nombre no puede tener mas de 60 caracteres." << endl;
				}
				else {

					regex formato_nombre("^[A-Za-z ]+$");

					if (!regex_match(nombres, formato_nombre)) {

						cout << "Error: El nombre solo debe contener letras y espacios." << endl;
					}
					else {

						nombres_validos = true;
					}
				}

			} while (!nombres_validos);

			// VALIDACION APELLIDOS

			bool apellidos_validos = false;

			do {

				cout << "Ingrese Apellidos: ";
				getline(cin, apellidos);

				if (apellidos.empty()) {

					cout << "Error: El apellido es obligatorio." << endl;
				}
				else if (apellidos.length() > 60) {

					cout << "Error: El apellido no puede tener mas de 60 caracteres." << endl;
				}
				else {

					regex formato_apellido("^[A-Za-z ]+$");

					if (!regex_match(apellidos, formato_apellido)) {

						cout << "Error: El apellido solo debe contener letras y espacios." << endl;
					}
					else {

						apellidos_validos = true;
					}
				}

			} while (!apellidos_validos);

			// VALIDACION DIRECCION

			bool direccion_valida = false;

			do {

				cout << "Ingrese Direccion: ";
				getline(cin, direccion);

				if (direccion.empty()) {

					cout << "Error: La direccion es obligatoria." << endl;
				}
				else if (direccion.length() > 100) {

					cout << "Error: La direccion no puede tener mas de 100 caracteres." << endl;
				}
				else {

					regex caracteres_peligrosos(
						"('|\"|;|--|=|<|>|DROP|DELETE|INSERT|UPDATE|SELECT)",
						regex_constants::icase
					);

					if (regex_search(direccion, caracteres_peligrosos)) {

						cout << "Error: La direccion contiene caracteres o palabras no permitidas." << endl;
					}
					else {

						direccion_valida = true;
					}
				}

			} while (!direccion_valida);

			// VALIDACION TELEFONO

			bool telefono_valido = false;

			do {

				cout << "Ingrese Telefono: ";
				getline(cin, telefono);

				if (telefono.empty()) {

					cout << "Error: El telefono es obligatorio." << endl;
				}
				else {

					regex formato_telefono("^[0-9]{8}$");

					if (!regex_match(telefono, formato_telefono)) {

						cout << "Error: El telefono debe contener exactamente 8 numeros." << endl;
					}
					else {

						telefono_valido = true;
					}
				}

			} while (!telefono_valido);

			// VALIDACION FECHA NACIMIENTO

			bool fecha_valida = false;

			do {

				cout << "Ingrese Fecha Nacimiento (AAAA-MM-DD): ";
				getline(cin, fecha_nacimiento);

				if (fecha_nacimiento.empty()) {

					cout << "Error: La fecha es obligatoria." << endl;
				}
				else {

					regex formato_fecha("^\\d{4}-\\d{2}-\\d{2}$");

					if (!regex_match(fecha_nacimiento, formato_fecha)) {

						cout << "Error: Formato invalido. Use AAAA-MM-DD." << endl;
					}
					else {

						int anio = stoi(fecha_nacimiento.substr(0, 4));
						int mes = stoi(fecha_nacimiento.substr(5, 2));
						int dia = stoi(fecha_nacimiento.substr(8, 2));

						bool fecha_correcta = true;

						// VALIDAR MES

						if (mes < 1 || mes > 12) {

							fecha_correcta = false;
						}

						// DIAS POR MES

						int dias_mes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

						// AÑO BISIESTO

						if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {

							dias_mes[1] = 29;
						}

						// VALIDAR DIA

						if (fecha_correcta) {

							if (dia < 1 || dia > dias_mes[mes - 1]) {

								fecha_correcta = false;
							}
						}

						// VALIDAR FECHA FUTURA

						time_t t = time(0);

						tm tiempo;

						localtime_s(&tiempo, &t);

						int anio_actual = tiempo.tm_year + 1900;
						int mes_actual = tiempo.tm_mon + 1;
						int dia_actual = tiempo.tm_mday;

						if (
							anio > anio_actual ||
							(anio == anio_actual && mes > mes_actual) ||
							(anio == anio_actual && mes == mes_actual && dia > dia_actual)
							) {

							fecha_correcta = false;
						}

						if (!fecha_correcta) {

							cout << "Error: La fecha no es valida o es futura." << endl;
						}
						else {

							fecha_valida = true;
						}
					}
				}

			} while (!fecha_valida);

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

			// VALIDACION NOMBRES

			bool nombres_validos = false;

			do {

				cout << "Ingrese Nombres: ";
				getline(cin, nombres);

				if (nombres.empty()) {

					cout << "Error: El nombre es obligatorio." << endl;
				}
				else if (nombres.length() > 60) {

					cout << "Error: El nombre no puede tener mas de 60 caracteres." << endl;
				}
				else {

					regex formato_nombre("^[A-Za-z ]+$");

					if (!regex_match(nombres, formato_nombre)) {

						cout << "Error: El nombre solo debe contener letras y espacios." << endl;
					}
					else {

						nombres_validos = true;
					}
				}

			} while (!nombres_validos);

			// VALIDACION APELLIDOS

			bool apellidos_validos = false;

			do {

				cout << "Ingrese Apellidos: ";
				getline(cin, apellidos);

				if (apellidos.empty()) {

					cout << "Error: El apellido es obligatorio." << endl;
				}
				else if (apellidos.length() > 60) {

					cout << "Error: El apellido no puede tener mas de 60 caracteres." << endl;
				}
				else {

					regex formato_apellido("^[A-Za-z ]+$");

					if (!regex_match(apellidos, formato_apellido)) {

						cout << "Error: El apellido solo debe contener letras y espacios." << endl;
					}
					else {

						apellidos_validos = true;
					}
				}

			} while (!apellidos_validos);

			// VALIDACION DIRECCION

			bool direccion_valida = false;

			do {

				cout << "Ingrese Direccion: ";
				getline(cin, direccion);

				if (direccion.empty()) {

					cout << "Error: La direccion es obligatoria." << endl;
				}
				else if (direccion.length() > 100) {

					cout << "Error: La direccion no puede tener mas de 100 caracteres." << endl;
				}
				else {

					regex caracteres_peligrosos(
						"('|\"|;|--|=|<|>|DROP|DELETE|INSERT|UPDATE|SELECT)",
						regex_constants::icase
					);

					if (regex_search(direccion, caracteres_peligrosos)) {

						cout << "Error: La direccion contiene caracteres o palabras no permitidas." << endl;
					}
					else {

						direccion_valida = true;
					}
				}

			} while (!direccion_valida);

			// VALIDACION TELEFONO

			bool telefono_valido = false;

			do {

				cout << "Ingrese Telefono: ";
				getline(cin, telefono);

				if (telefono.empty()) {

					cout << "Error: El telefono es obligatorio." << endl;
				}
				else {

					regex formato_telefono("^[0-9]{8}$");

					if (!regex_match(telefono, formato_telefono)) {

						cout << "Error: El telefono debe contener exactamente 8 numeros." << endl;
					}
					else {

						telefono_valido = true;
					}
				}

			} while (!telefono_valido);

			// VALIDACION FECHA NACIMIENTO

			bool fecha_valida = false;

			do {

				cout << "Ingrese Fecha Nacimiento (AAAA-MM-DD): ";
				getline(cin, fecha_nacimiento);

				if (fecha_nacimiento.empty()) {

					cout << "Error: La fecha es obligatoria." << endl;
				}
				else {

					regex formato_fecha("^\\d{4}-\\d{2}-\\d{2}$");

					if (!regex_match(fecha_nacimiento, formato_fecha)) {

						cout << "Error: Formato invalido. Use AAAA-MM-DD." << endl;
					}
					else {

						int anio = stoi(fecha_nacimiento.substr(0, 4));
						int mes = stoi(fecha_nacimiento.substr(5, 2));
						int dia = stoi(fecha_nacimiento.substr(8, 2));

						bool fecha_correcta = true;

						// VALIDAR MES

						if (mes < 1 || mes > 12) {

							fecha_correcta = false;
						}

						// DIAS POR MES

						int dias_mes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

						// AÑO BISIESTO

						if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {

							dias_mes[1] = 29;
						}

						// VALIDAR DIA

						if (fecha_correcta) {

							if (dia < 1 || dia > dias_mes[mes - 1]) {

								fecha_correcta = false;
							}
						}

						// VALIDAR FECHA FUTURA

						time_t t = time(0);

						tm tiempo;

						localtime_s(&tiempo, &t);

						int anio_actual = tiempo.tm_year + 1900;
						int mes_actual = tiempo.tm_mon + 1;
						int dia_actual = tiempo.tm_mday;

						if (
							anio > anio_actual ||
							(anio == anio_actual && mes > mes_actual) ||
							(anio == anio_actual && mes == mes_actual && dia > dia_actual)
							) {

							fecha_correcta = false;
						}

						if (!fecha_correcta) {

							cout << "Error: La fecha no es valida o es futura." << endl;
						}
						else {

							fecha_valida = true;
						}
					}
				}

			} while (!fecha_valida);

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