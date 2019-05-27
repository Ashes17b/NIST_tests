#include "runs_test_boltach.hpp"
// #include "random_excursion_variant_test.hpp"

using namespace runs_test;

int main()
{
    Runs_test_boltach r_test("../seq/seq3.bin");

    auto t1 = std::chrono::high_resolution_clock::now();
    r_test.read();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration_read = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on read(seconds): %.8f\n", duration_read);

    t1 = std::chrono::high_resolution_clock::now();
    auto p_value = r_test.run_test();
    t2 = std::chrono::high_resolution_clock::now();
    auto duration_task = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() * 1e-6;
    printf("Time spent on task(seconds): %.8f\n", duration_task);

    printf("Time spent on everything(seconds): %.8f\n", duration_read + duration_task);

    printf("\nP-value runs_test: %.8f\n", p_value);

    // random_excursion_variant_test::run("../seq/seq1.bin");

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