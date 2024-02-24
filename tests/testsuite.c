#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/tinyprintf.h"
#include <stdio.h>

Test(Basic, first)
{
    int count = 17;
    cr_redirect_stdout();
    int expected = tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_expect_stdout_eq_str("Hello [42] world!");
    cr_expect_eq(count, expected, "Expected %d got %d", expected, count);
}

Test(Basic, second)
{
    cr_redirect_stdout();
    tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_expect_stdout_eq_str("Hello [2a] world!");
}

Test(Basic, third)
{
    cr_redirect_stdout();
    tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    fflush(stdout);
    cr_expect_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
}

Test(Basic, fourth)
{
    cr_redirect_stdout();
    tinyprintf("%%s", "in your head");
    fflush(stdout);
    cr_expect_stdout_eq_str("%s");
}

Test(Basic, fifth)
{
    cr_redirect_stdout();
    tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", '*');
    fflush(stdout);
    cr_expect_stdout_eq_str("42 is the answer... 42 too.");
}

Test(Basic, six)
{
    cr_redirect_stdout();
    tinyprintf("%u is Great !", -100);
    fflush(stdout);
    cr_expect_stdout_eq_str("4294967196 is Great !");
}

Test(Basic, seven)
{
    cr_redirect_stdout();
    tinyprintf("%o is Great !", 100);
    fflush(stdout);
    cr_expect_stdout_eq_str("144 is Great !");
}

Test(Basic, eight)
{
    cr_redirect_stdout();
    tinyprintf("%s",NULL);
    fflush(stdout);
    cr_expect_stdout_eq_str("(null)");
}

Test(Basic, nine)
{
    cr_redirect_stdout();
    tinyprintf("%o is Great !", -15);
    fflush(stdout);
    cr_expect_stdout_eq_str("37777777761 is Great !");
}

Test(Basic, ten)
{
    cr_redirect_stdout();
    tinyprintf("%d is Great !", -15);
    fflush(stdout);
    cr_expect_stdout_eq_str("-15 is Great !");
}

Test(Basic, eleven)
{
    cr_redirect_stdout();
    tinyprintf("%d is Great !", 0);
    fflush(stdout);
    cr_expect_stdout_eq_str("0 is Great !");
}
