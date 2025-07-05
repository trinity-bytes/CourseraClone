#pragma once

#include <ctime>
#include <string>

std::string meses[12] = {
            "enero","febrero","marzo","abril","mayo","junio",
            "julio","agosto","setiembre","octubre","noviembre","diciembre"
};

// --- Clase única DateTime: obtiene y formatea fecha y hora ---
class DateTime {
public:
    // Captura fecha y hora actuales del sistema
    static DateTime now() {
        std::time_t t = std::time(nullptr);
        std::tm tm{};

        localtime_s(&tm, &t);
        return DateTime(
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec
        );
    }

    // Constructor
    DateTime(int year, int month, int day,
        int hour, int minute, int second)
        : _year(year), _month(month), _day(day),
        _hour(hour), _minute(minute), _second(second) {
    }

    static std::vector<std::string> obtenerUltimosTrimestres(int cantidad) {

        DateTime actual = DateTime::now();
        int year = actual._year;
        int month = actual._month;

        int trimestre = (month - 1) / 3 + 1;

        std::vector<std::string> res;

        for (int i = 0; i < cantidad; ++i) {
            res.push_back("Q" + std::to_string(trimestre)
                + " " + std::to_string(year));
            --trimestre;
            if (trimestre == 0) {
                trimestre = 4;
                --year;
            }
        }
        return res;
    }

    static std::string trimestreQ(int mes, int anio) {
        int q = (mes - 1) / 3 + 1;
        return "Q" + std::to_string(q) + " " + std::to_string(anio);
    }

    // "YYYY-MM-DD"
    static std::string toTrimestreString(std::string fecha) {
        auto convertidorFechaNumero = [](std::string fecha, int index, int cantidad) {
            std::string texto = fecha.substr(index, cantidad);
            return stoi(texto);
            };

        int mes = convertidorFechaNumero(fecha, 5, 2);
        int q = (mes - 1) / 3 + 1;

        int anio = convertidorFechaNumero(fecha, 0, 4);

        std::string res = trimestreQ(mes, anio);
        return res;
    }



    // Fecha en formato "DD de <mes>, YYYY"
    std::string toLongDateString() const {
        
        std::string s;
        if (_day < 10) s += '0';
        s += std::to_string(_day);
        s += " de ";
        s += meses[_month - 1];
        s += ", ";
        s += std::to_string(_year);
        return s;
    }

    std::string toDateNormalString() {
        std::string s;
        if (_day < 10) s += '0';
        s += std::to_string(_day);
        s += '/';
        if (_month < 10) s += '0';
        s += std::to_string(_month);
        s += '/';
        s += std::to_string(_year);
        return s;
    }

    // Fecha ISO "YYYY-MM-DD"
    std::string toIsoDateString() const {
        std::string s;
        s += std::to_string(_year);
        s += '-';
        if (_month < 10) s += '0';
        s += std::to_string(_month);
        s += '-';
        if (_day < 10) s += '0';
        s += std::to_string(_day);
        return s;
    }

    // Hora "HH:MM:SS"
    std::string toTimeString() const {
        std::string s;
        if (_hour < 10) s += '0';
        s += std::to_string(_hour);
        s += ':';
        if (_minute < 10) s += '0';
        s += std::to_string(_minute);
        s += ':';
        if (_second < 10) s += '0';
        s += std::to_string(_second);
        return s;
    }

    int getYear() {
        return _year;
    }

private:
    int _year, _month, _day;
    int _hour, _minute, _second;
};

