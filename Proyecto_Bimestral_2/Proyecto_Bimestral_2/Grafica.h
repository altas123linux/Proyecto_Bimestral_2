#ifndef GRAFICA_H
#define GRAFICA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

struct Restriccion {
    double coefX1;
    double coefX2;
    double constante;
    std::string operador;
    std::string nombre;
};

struct Punto {
    double x;
    double y;
    std::string etiqueta;
};

class GeneradorGrafica {
private:
    std::vector<Restriccion> restricciones;
    double puntoOptimoX, puntoOptimoY;
    double valorZ;
    
    void escribirArchivoGnuplot() {
        std::ofstream archivo("grafica.gp");
        
        archivo << "set title 'Solucion Grafica del Problema de Optimizacion - Flair Furniture'\n";
        archivo << "set xlabel 'x1 (Numero de mesas)'\n";
        archivo << "set ylabel 'x2 (Numero de sillas)'\n";
        archivo << "set grid\n";
        archivo << "set xrange [0:60]\n";
        archivo << "set yrange [0:50]\n";
        
        // Definir colores para las líneas
        archivo << "set style line 1 lc rgb 'red' lw 2\n";
        archivo << "set style line 2 lc rgb 'blue' lw 2\n";
        archivo << "set style line 3 lc rgb 'green' lw 2\n";
        archivo << "set style line 4 lc rgb 'purple' lw 2\n";
        archivo << "set style line 5 lc rgb 'orange' lw 2\n";
        
        archivo << "plot ";
        
        // Agregar cada restricción como una línea
        for(int i = 0; i < restricciones.size(); i++) {
            if(restricciones[i].coefX2 != 0) {
                // Calcular puntos para dibujar la línea: ax1 + bx2 = c
                double pendiente = -restricciones[i].coefX1 / restricciones[i].coefX2;
                double intercepto = restricciones[i].constante / restricciones[i].coefX2;
                
                archivo << "(" << intercepto << " + " << pendiente << "*x)";
                archivo << " with lines linestyle " << (i+1);
                archivo << " title '" << restricciones[i].nombre << "'";
                
                if(i < restricciones.size() - 1) archivo << ", ";
            }
        }
        
        // Agregar punto óptimo
        archivo << ", '-' with points pointtype 7 pointsize 2 lc rgb 'black' title 'Punto Optimo'\n";
        archivo << puntoOptimoX << " " << puntoOptimoY << "\n";
        archivo << "e\n";
        
        // Sombrear región factible (simplificado)
        archivo << "set object 1 polygon from ";
        archivo << "0,0 to 0," << (restricciones[1].constante/restricciones[1].coefX2);
        archivo << " to " << puntoOptimoX << "," << puntoOptimoY;
        archivo << " to " << (restricciones[0].constante/restricciones[0].coefX1) << ",0";
        archivo << " to 0,0\n";
        archivo << "set object 1 fillstyle solid 0.2 fillcolor 'yellow'\n";
        
        archivo << "replot\n";
        archivo << "pause -1\n";
        
        archivo.close();
    }
    
public:
    void agregarRestriccion(double coefX1, double coefX2, double constante, 
                           std::string operador, std::string nombre) {
        Restriccion r;
        r.coefX1 = coefX1;
        r.coefX2 = coefX2;
        r.constante = constante;
        r.operador = operador;
        r.nombre = nombre;
        restricciones.push_back(r);
    }
    
    void establecerPuntoOptimo(double x, double y, double z) {
        puntoOptimoX = x;
        puntoOptimoY = y;
        valorZ = z;
    }
    
    void generarGrafica() {
        escribirArchivoGnuplot();
        
        std::cout << "\nGenerando grafica...\n";
        std::cout << "Ejecutando: gnuplot grafica.gp\n";
        
        // Ejecutar gnuplot
        int resultado = system("gnuplot grafica.gp");
        
        if(resultado == 0) {
            std::cout << "Grafica generada exitosamente!\n";
        } else {
            std::cout << "Error al generar la grafica. Verifique que gnuplot este instalado.\n";
        }
    }
    
    void mostrarInformacion() {
        std::cout << "\n=== INFORMACION DE LA GRAFICA ===\n";
        std::cout << "Restricciones:\n";
        for(const auto& r : restricciones) {
            std::cout << "- " << r.nombre << ": " << r.coefX1 << "x1 + " 
                     << r.coefX2 << "x2 " << r.operador << " " << r.constante << "\n";
        }
        std::cout << "\nPunto optimo: (" << puntoOptimoX << ", " << puntoOptimoY << ")\n";
        std::cout << "Valor maximo de Z: " << valorZ << " USD\n";
    }
    
    void limpiarRestricciones() {
        restricciones.clear();
    }
};

#endif // GRAFICA_H