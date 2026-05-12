#include <iostream>
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

			cout << "Ingrese Codigo: ";
			cin >> codigo;
			cin.ignore();

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

			cout << "Ingrese Codigo: ";
			cin >> codigo;
			cin.ignore();

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