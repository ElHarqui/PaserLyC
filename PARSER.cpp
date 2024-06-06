#include <iostream>
#include <regex>
#include <string>

using namespace std;

void Imprimir_Palabras_Regex(string s, regex chars_regex);

int main() {
    while (1) {
        // DECLARACION DE PALABRAS RESERVADAS
        const string Reserved_Words 	= "\\b(PARA|SI|MIENTRAS|PRINCIPAL)";
        const string Parentesis_Chars 	= "\\(\\s*(([a-zA-Z]\\w*)\\s?,\\s?)*([a-zA-Z]\\w*)\\s*\\)";
        
        // Cadena de texto de ejemplo
        string s;
        cout << "-->";
        getline(cin, s);

        // Expresión regular para buscar palabras reservadas (insensible a mayúsculas y minúsculas)
        regex reserved_words_regex(Reserved_Words, regex_constants::ECMAScript | regex_constants::icase);
        if (regex_search(s, reserved_words_regex)) {
            cout << "\tPalabras reservadas encontradas :\n"; 
        }
		Imprimir_Palabras_Regex(s, reserved_words_regex);
		
        // Expresión regular para buscar caracteres en paréntesis (insensible a mayúsculas y minúsculas)
        regex parentesis_chars_regex(Parentesis_Chars, regex_constants::ECMAScript | regex_constants::icase);
        if (regex_search(s, parentesis_chars_regex)) {
            cout << "\tParéntesis encontrados :\n";          
        }
		Imprimir_Palabras_Regex(s, parentesis_chars_regex);
    }

    return 0; // Indica que la ejecución del programa terminó correctamente
}

void Imprimir_Palabras_Regex(string s, regex chars_regex) {
    // Inicializa un iterador para buscar todas las palabras en la cadena de texto
    sregex_iterator words_begin(s.begin(), s.end(), chars_regex);
    sregex_iterator words_end;
    
    // Imprime el número total de palabras encontradas en la cadena de texto
    cout << distance(words_begin, words_end) << "\n";

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        cout << "  " << match.str() << " "; // Imprime cada palabra encontrada
    }
    cout << "\n";
}


