<div class="no-overflow"><h1>Kolejki napisów</h1>

<h2>Wstęp</h2>

<p>Biblioteka standardowa języka C++ udostępnia bardzo przydatne kontenery, np.
<code>unordered_map</code> i <code>deque</code>, których nie ma w bibliotece C.</p>

<p>Często potrzebujemy łączyć kod C++ z kodem spadkowym w C. Celem tego zadania
jest napisanie w C++ modułu obsługującego kolejki napisów, tak aby można ich
używać w C. Moduł składa się z pliku nagłówkowego (z rozszerzeniem <code>.h</code>) i pliku
z implementacją (z rozszerzeniem <code>.cpp</code>).</p>

<p>Rozwiązując to zadanie, studenci powinni poznać:</p>

<ul>
<li>kolejne kontenery z STL,</li>
<li>sposób łączenia kodu w C++ z kodem w C,</li>
<li>metody inicjowania obiektów globalnych w C++ i wynikające stąd problemy,</li>
<li>preprocesor, elementy kompilowania warunkowego.</li>
</ul>

<h2>Polecenie</h2>

<p>Moduł <code>strqueue</code> powinien udostępniać następujące funkcje.</p>

<pre><code>unsigned long strqueue_new();
</code></pre>

<p>Tworzy nową, pustą kolejkę napisów i zwraca jej identyfikator.</p>

<pre><code>void strqueue_delete(unsigned long id);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze <code>id</code>, usuwa ją, a w przeciwnym
przypadku nic nie robi.</p>

<pre><code>size_t strqueue_size(unsigned long id);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze id, zwraca liczbę jej
elementów, a w przeciwnym przypadku zwraca 0.</p>

<pre><code>void strqueue_insert_at(unsigned long id, size_t position, const char* str);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze <code>id</code> oraz <code>str != NULL</code>,
wstawia napis <code>str</code> przed pozycją <code>position</code> lub na koniec kolejki, jeżeli
wartość <code>position</code> jest większa lub równa liczbie napisów w kolejce.
Jeżeli kolejka nie istnieje lub <code>str == NULL</code>, to nic nie robi.
Pozycje w kolejce numerowane są od zera.</p>

<pre><code>void strqueue_remove_at(unsigned long id, size_t position);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze <code>id</code> i wartość <code>position</code>
jest mniejsza niż liczba napisów w kolejce, usuwa napis na pozycji <code>position</code>,
a w przeciwnym przypadku nic nie robi.</p>

<pre><code>const char* strqueue_get_at(unsigned long id, size_t position);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze <code>id</code> i wartość <code>position</code>
jest mniejsza niż liczba napisów w kolejce, zwraca wskaźnik do napisu na pozycji
<code>position</code>, a w przeciwnym przypadku zwraca wartość <code>NULL</code>.</p>

<pre><code>void strqueue_clear(unsigned long id);
</code></pre>

<p>Jeżeli istnieje kolejka napisów o identyfikatorze <code>id</code>, usuwa z niej wszystkie
napisy, a w przeciwnym przypadki nic nie robi.</p>

<pre><code>int strqueue_comp(unsigned long id1, unsigned long id2);
</code></pre>

<p>Porównuje leksykograficznie kolejki napisów o identyfikatorach <code>id1</code> i <code>id2</code>,
zwracając</p>

<ul>
<li><code>-1</code>, gdy <code>kolejka(id1) &lt; kolejka(id2)</code>,</li>
<li><code>0</code>, gdy <code>kolejka(id1) == kolejka(id2)</code>,</li>
<li><code>1</code>, gdy <code>kolejka(id1) &gt; kolejka(id2)</code>.</li>
</ul>

<p>Jeżeli kolejka napisów o którymś z identyfikatorów nie istnieje, to jest
traktowana jak kolejka pusta.</p>

<h2>Wymagania formalne</h2>

<p>Oczekiwane rozwiązanie powinno korzystać z kontenerów i metod udostępnianych
przez standardową bibliotekę C++. Nie należy definiować własnych struktur, unii
lub klas.</p>

<p>Kolejka napisów powinna przechowywać kopie napisów, a nie wartości przekazanych
jej wskaźników.</p>

<p>Powinna być też możliwość używania wyżej opisanych funkcji w języku C++. Przy
kompilowaniu pliku nagłówkowego modułu w C++ deklaracje funkcji powinny znaleźć
się w przestrzeni nazw <code>cxx</code>.</p>

<p>Należy ukryć przed światem zewnętrznym wszystkie zmienne globalne i funkcje
pomocnicze nienależące do wyspecyfikowanego interfejsu modułu.</p>

<p>Funkcje powinny wypisywać na standardowe wyjście diagnostyczne informacje
o parametrach wywołania i wyniku wykonania. Szczegółowy format komunikatów
diagnostycznych pokazują poniżej zamieszczone przykłady użycia. Zachowanie
niezmienników i spójność danych można sprawdzać za pomocą asercji. Kompilowanie
z parametrem <code>-DNDEBUG</code> powinno wyłączać wypisywanie informacji diagnostycznych
i asercje. Obsługa standardowego wyjścia diagnostycznego powinna być realizowana
z użyciem strumienia C++, czyli biblioteki <code>iostream</code>.</p>

<p>Nie należy nadużywać kompilowania warunkowego. Fragmenty tekstu źródłowego
realizujące wyspecyfikowane operacje na kolejkach nie powinny zależeć od sposobu
kompilowania (parametr <code>-DNDEBUG</code> lub jego brak) – inaczej posiadanie wersji
diagnostycznej nie miałoby sensu.</p>

<p>Rozwiązanie powinno zawierać pliki <code>strqueue.h</code> i <code>strqueue.cpp</code>, które należy
umieścić w Moodle.</p>

<p>Rozwiązanie będzie kompilowane i testowane na maszynie students.</p>

<h2>Ocenianie rozwiązania</h2>

<h3>Ocena automatyczna</h3>

<p>Za testy automatyczne zostanie przyznana ocena z przedziału od 0 do 6 punków.
Za błędną nazwę pliku zostanie odjęty 1 punkt. Za ostrzeżenia wypisywane przez
kompilator zostanie odjęty 1 punkt. Nie ma punktów ułamkowych.</p>

<h3>Ocena jakości kodu</h3>

<p>Ocena jakości kodu jest z przedziału od 0 do 4 punktów. Nie ma punktów
ułamkowych. Odejmujemy punkty za:</p>

<ul>
<li>brzydki <a class="autolink" title="Styl" href="https://moodle.mimuw.edu.pl/mod/page/view.php?id=141465">styl</a> (niepoprawne wstawianie spacji, wcięć, odstępów, brak
komentarzy, magiczne stałe itd.);</li>
<li>dłubanie własnych klas, struktur lub algorytmów zamiast użycia STL-owych;</li>
<li>zły dobór typu lub kontenera, brak nazw typów, niewiele mówiące nazwy typów;</li>
<li>rozwlekłą lub nieelegancką strukturę programu, rozpatrywanie zbyt wielu
warunków brzegowych, powtarzanie kodu, nieefektywne korzystanie z klasy
<code>string</code>, np. <code>if (str != "")</code> zamiast <code>if (!str.empty())</code>, przechowywanie
liczb jako napisów;</li>
<li>korzystanie z wejścia-wyjścia dostarczanego przez bibliotekę C zamiast ze
strumieni;</li>
<li>wprowadzanie sztucznych ograniczeń na rozmiar danych;</li>
<li>nieusuwanie lub nieefektywne usuwanie niepotrzebnych już danych;</li>
<li>nieskuteczną obsługę (lub jej brak) problemu „static initialization order
fiasco” (czytanka „Inicjowanie obiektów globalnych”), o ile nie zostanie to
wykryte przez testy automatyczne; inicjowanie strumienia diagnostycznego
w każdej funkcji (przez powielenie kodu inicjującego);</li>
<li>niepoprawne pliki nagłówkowe, czyli brak <em>include guard</em>
<code>#ifndef #define #endif</code> lub <code>#ifdef __cplusplus</code>;</li>
<li>użycie <code>#if</code> zamiast <code>if constexpr</code> lub nieużycie <code>if constexpr</code>;</li>
<li>nieukrycie przed światem zewnętrznym wszystkich zmiennych globalnych i funkcji
pomocniczych nienależących do wyspecyfikowanego interfejsu modułu;</li>
<li>uzależnienie fragmentów tekstu źródłowego realizujące wyspecyfikowane operacje
na kolejkach od sposobu kompilowania (parametr <code>-DNDEBUG</code> lub jego brak);</li>
<li>braki w wypisywanych informacjach diagnostycznych; wypisywanie informacji
diagnostycznych w złych miejscach, np. informacja o wywołaniu funkcji powinna
być wypisana na początku, zanim funkcja zacznie coś robić, a informacja
o wykonaniu dopiero wtedy, gdy struktura danych została poprawnie
zmodyfikowana lub zbadana;</li>
<li>użycie <code>typedef</code> zamiast <code>using</code>;</li>
<li>błędy w stosowaniu przestrzeni nazw;</li>
<li>wielokrotne wyszukiwanie tego samego klucza w mapie;</li>
<li>inne znalezione i niewymienione w powyższych kryteriach błędy niewykryte przez
testy automatyczne.</li>
</ul>

<p>Ponadto piętnujemy:</p>

<ul>
<li>przekazywanie funkcjom dużych argumentów przez wartość – takie obiekty
przekazujemy przez stałą referencję, czyli <code>const &amp;</code>; na razie tylko
wskazujemy te błędy i nie odejmujemy za nie punktów, bo są to zagadnienia
pojawiające się w kolejnych zadaniach, w których już będziemy za to karać.</li>
</ul>

<h2>Przykłady użycia</h2>

<p>Przykłady użycia znajdują się w plikach <code>strqueue_test_1.c</code>
i <code>strqueue_test_2.cpp</code>. Przykłady informacji diagnostycznych wypisywanych przez
<code>strqueue_test_1_dbg</code>, <code>strqueue_test_2_dbg_a</code> i <code>strqueue_test_2_dbg_b</code>
znajdują się w plikach <code>strqueue_test_1.log</code> i <code>strqueue_test_2.log</code>.</p>

<p>Kompilowanie przykładów:</p>

<pre><code>g++ -c -Wall -Wextra -O2 -std=c++17 strqueue.cpp -o strqueue_dbg.o
g++ -c -Wall -Wextra -O2 -std=c++17 -DNDEBUG strqueue.cpp -o strqueue_nodbg.o
gcc -c -Wall -Wextra -O2 -std=c17 strqueue_test_1.c -o strqueue_test_1.o
g++ -c -Wall -Wextra -O2 -std=c++17 strqueue_test_2.cpp -o strqueue_test_2.o
g++ strqueue_test_1.o strqueue_dbg.o -o strqueue_test_1_dbg
g++ strqueue_test_1.o strqueue_nodbg.o -o strqueue_test_1_nodbg
g++ strqueue_test_2.o strqueue_dbg.o -o strqueue_test_2_dbg_a
g++ strqueue_dbg.o strqueue_test_2.o -o strqueue_test_2_dbg_b
g++ strqueue_test_2.o strqueue_nodbg.o -o strqueue_test_2_nodbg
</code></pre>
</div>
