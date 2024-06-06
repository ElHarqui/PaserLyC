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

        // Expresi�n regular para buscar palabras reservadas (insensible a may�sculas y min�sculas)
        regex reserved_words_regex(Reserved_Words, regex_constants::ECMAScript | regex_constants::icase);
        if (regex_search(s, reserved_words_regex)) {
            cout << "\tPalabras reservadas encontradas :\n"; 
        }
		Imprimir_Palabras_Regex(s, reserved_words_regex);
		
        // Expresi�n regular para buscar caracteres en par�ntesis (insensible a may�sculas y min�sculas)
        regex parentesis_chars_regex(Parentesis_Chars, regex_constants::ECMAScript | regex_constants::icase);
        if (regex_search(s, parentesis_chars_regex)) {
            cout << "\tPar�ntesis encontrados :\n";          
        }
		Imprimir_Palabras_Regex(s, parentesis_chars_regex);
    }

    return 0; // Indica que la ejecuci�n del programa termin� correctamente
}

void Imprimir_Palabras_Regex(string s, regex chars_regex) {
    // Inicializa un iterador para buscar todas las palabras en la cadena de texto
    sregex_iterator words_begin(s.begin(), s.end(), chars_regex);
    sregex_iterator words_end;
    
    // Imprime el n�mero total de palabras encontradas en la cadena de texto
    cout << distance(words_begin, words_end) << "\n";

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        cout << "  " << match.str() << " "; // Imprime cada palabra encontrada
    }
    cout << "\n";
}

	
	
	/*
	auto words_inicio =
    
    // Expresi�n regular para buscar la frase "REGULAR EXPRESSIONS" (insensible a may�sculas y min�sculas)
    regex self_regex("REGULAR EXPRESSIONS", regex_constants::ECMAScript | regex_constants::icase);
    // Busca la expresi�n regular en la cadena de texto
    if (regex_search(s, self_regex))
	{
    	cout << "El texto contiene la frase 'regular expressions'\n";	
	}
      
	    
    // Expresi�n regular para encontrar palabras en la cadena de texto
    regex word_regex("(\\w+)");

    // Inicializa un iterador para buscar todas las palabras en la cadena de texto
    auto words_begin = sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end	 = sregex_iterator();

    // Imprime el n�mero total de palabras encontradas en la cadena de texto
    cout << "Encontramos "
         << distance(words_begin, words_end)
         << " palabras\n";

    // Define la longitud m�nima de las palabras a buscar
    const int N = 6;

    // Imprime todas las palabras m�s largas que N caracteres
    cout << "Palabras de  " << N << " caracteres:\n";
    for (sregex_iterator i = words_begin; i != words_end; ++i)
    {
        smatch match = *i;
        string match_str = match.str();
        if (match_str.size() > N)
        {
        	cout << "  " << match_str << '\n';
		}
            
    }

    // Expresi�n regular para encontrar palabras con m�s de 6 caracteres
    regex long_word_regex("(\\w{7,})");
		
    // Reemplaza las palabras largas con el formato "[palabra]" en la cadena de texto
    string new_s = regex_replace(s, long_word_regex, "[$&]");
	
    // Imprime la cadena de texto modificada
    cout << new_s << '\n';
    */

