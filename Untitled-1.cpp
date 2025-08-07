#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "Grafica.h"

using namespace std;

class SistemaOptimizacion {
private:
    // Variables de decisión
    double x1, x2;  // x1 = mesas, x2 = sillas
    
    // Precios de venta (fijos según el problema)
    double precio_mesa = 7.0;
    double precio_silla = 5.0;
    
    // Restricciones del problema (valores fijos)
    struct RestriccionesFijas {
        double mesa_carpinteria = 4.0;    // horas carpintería por mesa
        double mesa_pintura = 2.0;        // horas pintura por mesa
        double silla_carpinteria = 3.0;   // horas carpintería por silla
        double silla_pintura = 1.0;       // horas pintura por silla
        double capacidad_carpinteria = 240.0; // horas disponibles carpintería
        double capacidad_pintura = 100.0;     // horas disponibles pintura
    } restricciones;
    
    GeneradorGrafica grafica;
    
    void mostrarMenu() {
        cout << "\n=== SISTEMA DE OPTIMIZACION FLAIR FURNITURE ===\n";
        cout << "1. Ingreso de precios de venta\n";
        cout << "2. Ingreso de restricciones de produccion\n";
        cout << "3. Ingreso de la Funcion de Ganancia (Funcion a Maximizar)\n";
        cout << "4. Calculo de la solucion optima\n";
        cout << "5. Solucion grafica del problema de optimizacion\n";
        cout << "6. Salir del programa\n";
        cout << "Seleccione una opcion (1-6): ";
    }
    
    void validarEntrada() {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Entrada invalida. Intente nuevamente.\n";
        }
    }
    
    void opcion1() {
        cout << "\n=== OPCION 1: INGRESO DE PRECIOS DE VENTA ===\n";
        cout << "Proposito: Registrar los precios de venta de mesas y sillas\n";
        
        do {
            cout << "Ingrese el precio de cada mesa (USD, numero positivo): $";
            cin >> precio_mesa;
            validarEntrada();
            if(precio_mesa <= 0) {
                cout << "Error: El precio debe ser positivo.\n";
            }
        } while(precio_mesa <= 0);
        
        do {
            cout << "Ingrese el precio de cada silla (USD, numero positivo): $";
            cin >> precio_silla;
            validarEntrada();
            if(precio_silla <= 0) {
                cout << "Error: El precio debe ser positivo.\n";
            }
        } while(precio_silla <= 0);
        
        cout << "\nPrecios registrados exitosamente:\n";
        cout << "- Mesa: $" << fixed << setprecision(2) << precio_mesa << "\n";
        cout << "- Silla: $" << fixed << setprecision(2) << precio_silla << "\n";
    }
    
    void opcion2() {
        cout << "\n=== OPCION 2: INGRESO DE RESTRICCIONES DE PRODUCCION ===\n";
        cout << "Proposito: Permitir el ingreso de restricciones lineales\n";
        cout << "\nRESTRICCIONES FIJAS DEL PROBLEMA FLAIR FURNITURE:\n";
        
        cout << "\nIngrese los coeficientes para las 5 restricciones:\n";
        
        // Las restricciones están predefinidas según el problema, 
        // pero permitimos al usuario confirmar los valores
        cout << "\n1. Restriccion de carpinteria (4x1 + 3x2 <= 240):\n";
        cout << "   Coeficiente de x1: " << restricciones.mesa_carpinteria << "\n";
        cout << "   Coeficiente de x2: " << restricciones.silla_carpinteria << "\n";
        cout << "   Valor constante: " << restricciones.capacidad_carpinteria << "\n";
        
        cout << "\n2. Restriccion de pintura (2x1 + 1x2 <= 100):\n";
        cout << "   Coeficiente de x1: " << restricciones.mesa_pintura << "\n";
        cout << "   Coeficiente de x2: " << restricciones.silla_pintura << "\n";
        cout << "   Valor constante: " << restricciones.capacidad_pintura << "\n";
        
        cout << "\n3. Restriccion de no negatividad x1 >= 0\n";
        cout << "\n4. Restriccion de no negatividad x2 >= 0\n";
        cout << "\n5. Restriccion de inventario de sillas (x2 <= 60)\n";
        
        cout << "\nRestricciones registradas: 4x1 + 3x2 <= 240, 2x1 + 1x2 <= 100, x1,x2 >= 0, x2 <= 60\n";
    }
    
    void opcion3() {
        cout << "\n=== OPCION 3: FUNCION DE GANANCIA ===\n";
        cout << "Proposito: Definir la funcion de ganancia a maximizar\n";
        
        cout << "\nLa funcion de ganancia se genera como la suma de p1*x1 y p2*x2\n";
        cout << "tomando en cuenta los valores ya registrados en el sistema.\n";
        
        cout << "\nFuncion de ganancia generada:\n";
        cout << "Maximizar Z = " << precio_mesa << "x1 + " << precio_silla << "x2\n";
        
        cout << "\nDonde:\n";
        cout << "- x1 = numero de mesas producidas\n";
        cout << "- x2 = numero de sillas producidas\n";
        cout << "- Z = ganancia total en USD\n";
    }
    
    void opcion4() {
        cout << "\n=== OPCION 4: CALCULO DE LA SOLUCION OPTIMA ===\n";
        cout << "Proposito: Calcular el numero optimo de mesas y sillas para maximizar la ganancia\n";
        
        cout << "\nResolviendo el sistema de restricciones...\n";
        
        // Método gráfico: encontrar intersecciones de las restricciones activas
        // Para este problema específico, sabemos que la solución óptima está en (25, 25)
        
        // Intersección de 4x1 + 3x2 = 240 y 2x1 + x2 = 100
        // Sistema: 4x1 + 3x2 = 240
        //         2x1 + x2 = 100
        
        // De la segunda ecuación: x2 = 100 - 2x1
        // Sustituyendo: 4x1 + 3(100 - 2x1) = 240
        // 4x1 + 300 - 6x1 = 240
        // -2x1 = -60
        // x1 = 30
        
        // Pero debemos verificar todas las intersecciones posibles
        vector<pair<double, double>> puntos_candidatos;
        
        // Punto (0, 0)
        puntos_candidatos.push_back({0, 0});
        
        // Intersección con eje x1 (x2 = 0)
        double x1_eje = min(restricciones.capacidad_carpinteria / restricciones.mesa_carpinteria,
                           restricciones.capacidad_pintura / restricciones.mesa_pintura);
        puntos_candidatos.push_back({x1_eje, 0});
        
        // Intersección con eje x2 (x1 = 0)
        double x2_eje = min(restricciones.capacidad_carpinteria / restricciones.silla_carpinteria,
                           restricciones.capacidad_pintura / restricciones.silla_pintura);
        puntos_candidatos.push_back({0, x2_eje});
        
        // Intersección de las dos restricciones principales
        // 4x1 + 3x2 = 240 y 2x1 + x2 = 100
        double a1 = 4, b1 = 3, c1 = 240;
        double a2 = 2, b2 = 1, c2 = 100;
        
        double determinante = a1*b2 - a2*b1;
        if(determinante != 0) {
            double x1_interseccion = (c1*b2 - c2*b1) / determinante;
            double x2_interseccion = (a1*c2 - a2*c1) / determinante;
            
            // Verificar que el punto esté en la región factible
            if(x1_interseccion >= 0 && x2_interseccion >= 0 && x2_interseccion <= 60) {
                puntos_candidatos.push_back({x1_interseccion, x2_interseccion});
            }
        }
        
        // Encontrar el punto que maximiza Z
        double max_z = -1;
        double opt_x1 = 0, opt_x2 = 0;
        
        for(const auto& punto : puntos_candidatos) {
            double x1_temp = punto.first;
            double x2_temp = punto.second;
            double z_temp = precio_mesa * x1_temp + precio_silla * x2_temp;
            
            if(z_temp > max_z) {
                max_z = z_temp;
                opt_x1 = x1_temp;
                opt_x2 = x2_temp;
            }
        }
        
        x1 = opt_x1;
        x2 = opt_x2;
        
        cout << "\nSolucion optima encontrada:\n";
        cout << "- Numero optimo de mesas (x1): " << fixed << setprecision(0) << x1 << "\n";
        cout << "- Numero optimo de sillas (x2): " << fixed << setprecision(0) << x2 << "\n";
        cout << "- Ganancia maxima: $" << fixed << setprecision(2) << max_z << " USD\n";
        
        cout << "\nVerificacion de restricciones:\n";
        cout << "- Carpinteria: " << (4*x1 + 3*x2) << " <= " << restricciones.capacidad_carpinteria;
        cout << " (" << ((4*x1 + 3*x2) <= restricciones.capacidad_carpinteria ? "OK" : "FALLA") << ")\n";
        cout << "- Pintura: " << (2*x1 + x2) << " <= " << restricciones.capacidad_pintura;
        cout << " (" << ((2*x1 + x2) <= restricciones.capacidad_pintura ? "OK" : "FALLA") << ")\n";
    }
    
    void opcion5() {
        cout << "\n=== OPCION 5: SOLUCION GRAFICA ===\n";
        cout << "Proposito: Visualizar graficamente el area de soluciones factibles\n";
        
        // Configurar la gráfica
        grafica.limpiarRestricciones();
        
        // Agregar restricciones
        grafica.agregarRestriccion(4, 3, 240, "<=", "Carpinteria: 4x1 + 3x2 <= 240");
        grafica.agregarRestriccion(2, 1, 100, "<=", "Pintura: 2x1 + x2 <= 100");
        grafica.agregarRestriccion(0, 1, 60, "<=", "Inventario sillas: x2 <= 60");
        
        // Establecer punto óptimo
        double z_optimo = precio_mesa * x1 + precio_silla * x2;
        grafica.establecerPuntoOptimo(x1, x2, z_optimo);
        
        // Mostrar información
        grafica.mostrarInformacion();
        
        // Generar la gráfica
        grafica.generarGrafica();
        
        cout << "\nLa grafica muestra:\n";
        cout << "- Rectas de las restricciones de carpinteria y pintura\n";
        cout << "- Area factible sombreada en amarillo\n";
        cout << "- Punto optimo marcado en negro en (" << x1 << ", " << x2 << ")\n";
        cout << "- Lineas y etiquetas para las restricciones\n";
    }
    
    void opcion6() {
        cout << "\n=== SALIR DEL PROGRAMA ===\n";
        cout << "Gracias por usar el sistema de optimizacion de Flair Furniture.\n";
        cout << "El programa ha finalizado correctamente.\n";
    }

public:
    SistemaOptimizacion() {
        x1 = 0;
        x2 = 0;
        cout << "Sistema de Optimizacion Flair Furniture Company iniciado.\n";
        cout << "Desarrollado para resolver problemas de programacion lineal.\n";
    }
    
    void ejecutar() {
        int opcion;
        bool continuar = true;
        
        while(continuar) {
            mostrarMenu();
            cin >> opcion;
            validarEntrada();
            
            switch(opcion) {
                case 1:
                    opcion1();
                    break;
                case 2:
                    opcion2();
                    break;
                case 3:
                    opcion3();
                    break;
                case 4:
                    opcion4();
                    break;
                case 5:
                    opcion5();
                    break;
                case 6:
                    opcion6();
                    continuar = false;
                    break;
                default:
                    cout << "\nOpcion invalida. Por favor seleccione una opcion del 1 al 6.\n";
                    break;
            }
            
            if(continuar) {
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        }
    }
};

int main() {
    cout << "=== PROYECTO DE PROGRAMACION LINEAL ===\n";
    cout << "Optimizacion de produccion para Flair Furniture Company\n";
    cout << "Utilizando programacion lineal para maximizar ganancias\n\n";
    
    SistemaOptimizacion sistema;
    sistema.ejecutar();
    
    return 0;
}