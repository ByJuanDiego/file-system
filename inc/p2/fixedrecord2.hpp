#ifndef FILE_SYSTEM_FIXEDRECORD2_HPP
#define FILE_SYSTEM_FIXEDRECORD2_HPP

#include <fstream>
#include <utility>
#include <vector>

#include "student2.hpp"

namespace p2 {
    class fixed_record {

        std::fstream file;
        std::string file_name;

    public:
        explicit fixed_record(std::string file_name);

        ~fixed_record();

        std::vector<p2::student> load();

        void add(p2::student &record);

        p2::student read_record(int pos);

        void delete_record(int pos);
    };

    fixed_record::fixed_record(std::string file_name) : file_name(std::move(file_name)) {
    }

    fixed_record::~fixed_record() = default;

    std::vector<p2::student> fixed_record::load() {
        // abrir archivo
        // crear el vector
        // si el archivo no se abrio correctamente retornar vector vacio (o throw)
        // ignorar los primeros 4 bytes del header

        // definir int next_del = 0;
        // Loop de lectura :
        // siempre y cuando no este en el final
            // leer el next_del
            // si archivo.fail() break;
            // si next_del != 0 continue;
            // caso contrario regresar el cursor al inicio de ese registro y leer su informacion
            // regresar el cursor al inicio del byte siguiente a next_del
            // push_back del registro
        // cerrar arhcivo
        // retornar
    }

    void fixed_record::add(p2::student &record) {
        // abrir el archivo

        // definir first_del;
        // leer el valor de los primeros 4 bytes en una first_del

        // si first_del == -1 entonces agregar el record al final del archivo

        // caso contrario, ir a esa posicion, leer su valor de next_del y asignarlo en first_del
        // escribir el nuevo registro en esa posicion
        // escribir en el header el nuevo valor de first_del

        // cerrar el archivo
    }

    p2::student fixed_record::read_record(int pos) {
        // si pos es (-) throw;
        // abrir el archivo
        // si no pudo abrirse throw

        // avanzar los 4 bytes del header
        // saber cuantos bytes hay desde esa posicion hasta el final del archivo
        // calcular cuantos registros hay dividiendo

        // si pos >= cantidad de registros throw

        // sino, definir p2::student y int next_del = 0
        // leer la informacion de ese registro y asignar el valor a next_del
        // si next_del != 0, entonces throw
        // sino, retornar el student
    }

    void fixed_record::delete_record(int pos){
        // si pos < 0 throw

        // leer el header y asignarlo en una variable first_pos

        // despues, ignorar los siguientes (pos * record_size) bytes

        // guardar la posicion del cursor actual en una variable new_del
        // escribir el campo next_del del registro como first_pos, ya que ese sera el siguiente eliminado
        // reescribir el header com el valor de new_del, puesto q ese sera el nuevo primer eliminado

        // cerrar archivos
    }
}

#endif //FILE_SYSTEM_FIXEDRECORD2_HPP
