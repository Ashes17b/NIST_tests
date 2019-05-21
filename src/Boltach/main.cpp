#include <fstream>
#include <ctime>

#include "runs_test.hpp"
#include "random_excursion_variant_test.hpp"

void test1( const std::string filename ) 
{
    std::ifstream f(filename, std::ios::binary | std::ios::in);

    if ( !f.is_open() )
    {
        std::cout << "Could NOT find " + filename << std::endl;
        return;
    }

    clock_t tStart = clock();

    std::vector<int8_t> buffer;
    char c;
    while ( f.get(c) ) 
        for ( int i = 7; i >= 0; --i ) 
            buffer.push_back((((c >> i) & 1) * 2) - 1);
    
    f.close();

    std::cout << filename + ": ";
    printf( "P-value runs_test: %.8f\n", runs_test::test( buffer ) );
    printf( "Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC );
    std::cout << std::endl;
}

void test2(const std::string filename)
{
    std::ifstream f(filename, std::ios::binary | std::ios::in);

    if (!f.is_open())
    {
        std::cout << "Could NOT find " + filename << std::endl;
        return;
    }

    clock_t tStart = clock();

    std::vector<int8_t> buffer;

    char c;
    while (f.get(c))
        for (int i = 7; i >= 0; --i)
            buffer.push_back(((c >> i) & 1));

    f.close();

    std::cout << filename + ": ";
    printf( "P-value random_excursion_variant_test: %.8f\n", random_excursion_variant_test::test( buffer ) );
    printf("Time taken: %.4fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    std::cout << std::endl;
}

int main()
{
    test1( "../seq/seq1.bin" );
    test1( "../seq/seq2.bin" );
    test1( "../seq/seq3.bin" );
    test1( "../seq/seq4.bin" );
    test1( "../seq/seq5.bin" );
    test1( "../seq/seq6.bin" );
    test1( "../seq/seq7.bin" );
    test1( "../seq/seq8.bin" );

    test2("../seq/seq1.bin");
    test2("../seq/seq2.bin");
    test2("../seq/seq3.bin");
    test2("../seq/seq4.bin");
    test2("../seq/seq5.bin");
    test2("../seq/seq6.bin");
    test2("../seq/seq7.bin");
    test2("../seq/seq8.bin");

    return 0;
}

/** Count the one's.
 * Это тест count-1 для определенных байтов. 
 * Рассмотрим тестируемый файл как поток 32-битных целых чисел. 
 * Из каждого целого числа выбирается определенный байт, скажем, самые левые биты с 1 по 8. 
 * Каждый байт может содержать от 0 до 8 1 с вероятностями 1, 8, 28, 56, 70, 56, 28, 8, 1 над 256. 
 * Теперь позвольте указанным байтам из последовательных целых чисел 
 * предоставить строку (перекрывающихся) 5-буквенных слов, причем каждая «буква» принимает значения A, B, C, D, E. 
 * Буквы определяются числом 1, в этом байт 0, 1 или 2 -> A, 3 -> B, 4 -> C, 5 -> D и 6, 7 или 8 -> E. 
 * Таким образом, мы имеем обезьяну на пишущей машинке, ударяющую пять клавиш с различными вероятности 37, 56, 70, 56, 37 за 256. 
 * Есть 5 ^ 5 возможных 5-буквенных слов, и из строки из 256 000 (перекрывающихся) 5-буквенных слов производится 
 * подсчет частот для каждого слова. Квадратичная форма в слабой инверсии ковариационной матрицы подсчета клеток дает xi-тест Q5-Q4,
 * разность наивных сумм Пирсона (OBS - EXP) ^ 2 / EXP по подсчетам для 5- и 4-буквенной ячейки на счет.
*/