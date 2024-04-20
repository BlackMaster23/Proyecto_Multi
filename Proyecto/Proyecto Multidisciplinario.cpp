#include <iostream>
using namespace std;

float precios[10];
string nombres[10];
string nombresClientes[100]; // Supongamos un máximo de 100 ventas
string productosComprados[100][10]; // Máximo 10 productos por venta
float preciosTotales[100]; // Precios totales de cada venta
int numVentas = 0; // Contador de ventas realizadas

void ingresarDatos() {
    cout << "Ingresa los nombres de los productos: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Nombre del Producto : " << i + 1 << endl;
        cin >> nombres[i];
    }
    cout << "Ingresa los precios de los productos: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << nombres[i] << " : ";
        cin >> precios[i];
    }
}

void ordenardor() {
    int auxprecios;
    string auxNombre;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (precios[i] > precios[j]) {
                auxprecios = precios[i];
                auxNombre = nombres[i];
                precios[i] = precios[j];
                nombres[i] = nombres[j];
                precios[j] = auxprecios;
                nombres[j] = auxNombre;
            }
        }
    }
}

void VerLista() {
    cout << "Producto:::" << ":::Precio" << endl;
    for (int i = 0; i < 10; i++)
        cout << nombres[i] << "\t" << precios[i] << endl;
}

int contardor() {
    int contador = 0;
    for (int i = 0; i < 10; i++) {
        if (precios[i] == 0) {
            contador++;
        }
    }
    cout << contador << endl;
    return contador;
}

void venderProducto() {
    string cliente;
    cout << "Ingrese el nombre del cliente: ";
    cin >> cliente;

    float total = 0;
    string producto;
    int numProductos = 0;

    do {
        cout << "Ingrese el nombre del producto a vender: ";
        cin >> producto;

        // Verificar si el producto está en la lista de precios
        bool encontrado = false;
        for (int i = 0; i < 10; i++) {
            if (nombres[i] == producto) {
                encontrado = true;
                cout << "Precio del producto: " << precios[i] << endl;
                total += precios[i];
                productosComprados[numVentas][numProductos++] = producto; // Agregar el producto a la venta
                break;
            }
        }

        if (!encontrado) {
            cout << "El producto no se encuentra en la lista." << endl;
        }

        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> producto;
        // Verificar si el usuario ingresó una cadena vacía
        while (producto[0] != 's' && producto[0] != 'S' && producto[0] != 'n' && producto[0] != 'N') {
            cout << "Entrada inválida. Ingrese 's' para continuar o 'n' para finalizar: ";
            cin >> producto;
        }
    } while (producto[0] == 's' || producto[0] == 'S');

    // Guardar los datos de la venta
    nombresClientes[numVentas] = cliente;
    preciosTotales[numVentas] = total;
    numVentas++;

    // Imprimir información sobre la venta
    cout << "\nInformación de la venta:" << endl;
    cout << "Cliente: " << cliente << endl;
    cout << "Productos comprados:" << endl;
    for (int i = 0; i < numProductos; ++i) {
        cout << "- " << productosComprados[numVentas - 1][i] << endl;
    }
    cout << "Precio total: $" << total << endl;
    cout << endl;
}

void eliminarProducto() {
    string producto;
    cout << "Ingrese el nombre del producto a eliminar: ";
    cin >> producto;

    bool encontrado = false;
    for (int i = 0; i < 10; i++) {
        if (nombres[i] == producto) {
            encontrado = true;
            // Confirmar la eliminación del producto
            char confirmar;
            cout << "¿Está seguro de eliminar este producto? (s/n): ";
            cin >> confirmar;
            if (confirmar == 's' || confirmar == 'S') {
                // Eliminar el producto
                for (int j = i; j < 9; j++) {
                    nombres[j] = nombres[j + 1];
                    precios[j] = precios[j + 1];
                }
                nombres[9] = "";
                precios[9] = 0;
                cout << "Producto eliminado exitosamente." << endl;
            } else {
                cout << "Eliminación cancelada." << endl;
            }
            break;
        }
    }

    if (!encontrado)
        cout << "El producto no se encuentra en la lista." << endl;
}

void eliminarVentaPorNombre() {
	string nombreCliente;
    bool encontrado = false;
    
    for (int i = 0; i < numVentas; i++) {
        if (nombresClientes[i] == nombreCliente) {
            encontrado = true;
            // Eliminar datos de la venta
            for (int j = i; j < numVentas - 1; j++) {
                nombresClientes[j] = nombresClientes[j + 1];
                preciosTotales[j] = preciosTotales[j + 1];
                for (int k = 0; k < 10; k++) {
                    productosComprados[j][k] = productosComprados[j + 1][k];
                }
            }
            numVentas--;
            cout << "Venta del cliente '" << nombreCliente << "' eliminada exitosamente." << endl;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se encontró ninguna venta asociada al cliente '" << nombreCliente << "'." << endl;
    }
}

void verVentas() {
    cout << "Ventas realizadas:" << endl;
    for (int i = 0; i < numVentas; ++i) {
        cout << "Venta " << i + 1 << ":" << endl;
        cout << "Nombre del cliente: " << nombresClientes[i] << endl;
        cout << "Productos comprados: ";
        for (int j = 0; j < 10; ++j) {
            if (productosComprados[i][j] != "") {
                cout << productosComprados[i][j];
                if (j < 9 && productosComprados[i][j + 1] != "") {
                    cout << ", ";
                }
            }
        }
        cout << endl;
        cout << "Precio total: $" << preciosTotales[i] << endl;
        cout << endl;
    }
}

void Menu() {
    int opcion;
    do {
        cout << "1. :::::: Agregar Productos ::::: " << endl;
        cout << "2. ::::: Eliminar Productos ::::: " << endl;
        cout << "3. ::::: Lista De Productos ::::: " << endl;
        cout << "4. ::::::: Vender Productos ::::: " << endl;
        cout << "5.::::::::: Eliminar Ventas ::::: " << endl;
        cout << "6. ::::::::::::: Ver ventas ::::: " << endl;
        cout << "7. :::::::::::::::::: Salir ::::: " << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                ingresarDatos();
                ordenardor();
                break;
            case 2:
            	eliminarProducto();
                break;
            case 3:
                    VerLista();
                break;
            case 4:
            	venderProducto();
                break;
            case 5: {
                string nombreCliente;
                cout << "Ingrese el nombre del cliente cuya venta desea eliminar: ";
                cin >> nombreCliente;
                eliminarVentaPorNombre();
                break;
            }
            case 6:
                verVentas();
                break;
        }
    } while (opcion != 7);
}

int main() {
    Menu();
}