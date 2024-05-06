#include <iostream>   // Para entrada y salida estándar
#include <iterator>   // Para iteradores
#include <regex>      // Para expresiones regulares
#include <string>     // Para cadenas de texto

using namespace std; // Usa el espacio de nombres std por conveniencia

int main()
{
    while(1){
	    	// Cadena de texto de ejemplo
	    string s; 
	    cout << "->> "; cin>>s;
	    
	    // Expresión regular para buscar la frase "REGULAR EXPRESSIONS" (insensible a mayúsculas y minúsculas)
	    regex self_regex("REGULAR EXPRESSIONS",
	                     regex_constants::ECMAScript | regex_constants::icase);
	
	    // Busca la expresión regular en la cadena de texto
	    if (regex_search(s, self_regex))
	        cout << "El texto contiene la frase 'regular expressions'\n";
	
	    // Expresión regular para encontrar palabras en la cadena de texto
	    regex word_regex("(\\w+)");
	
	    // Inicializa un iterador para buscar todas las palabras en la cadena de texto
	    auto words_begin =
	        sregex_iterator(s.begin(), s.end(), word_regex);
	    auto words_end = sregex_iterator();
	
	    // Imprime el número total de palabras encontradas en la cadena de texto
	    cout << "Encontramos "
	         << distance(words_begin, words_end)
	         << " palabras\n";
	
	    // Define la longitud mínima de las palabras a buscar
	    const int N = 6;
	
	    // Imprime todas las palabras más largas que N caracteres
	    cout << "Palabras de  " << N << " caracteres:\n";
	    for (sregex_iterator i = words_begin; i != words_end; ++i)
	    {
	        smatch match = *i;
	        string match_str = match.str();
	        if (match_str.size() > N)
	            cout << "  " << match_str << '\n';
	    }
	
	    // Expresión regular para encontrar palabras con más de 6 caracteres
	    regex long_word_regex("(\\w{7,})");
	
	    // Reemplaza las palabras largas con el formato "[palabra]" en la cadena de texto
	    string new_s = regex_replace(s, long_word_regex, "[$&]");
	
	    // Imprime la cadena de texto modificada
	    cout << new_s << '\n';
	}

    return 0; // Indica que la ejecución del programa terminó correctamente
}

