#include <check.h>
#include <math.h>
#include "../obj_parcer.h"

#define EPS 1e-6

Model_data obj;

void setup(void) {
    // Инициализация объекта модели для тестов
    init_obj(&obj, 4);  // Предполагаем, что модель содержит 4 вершины
    obj.vertices[0].x = 1.0; obj.vertices[0].y = 2.0; obj.vertices[0].z = 3.0;
    obj.vertices[1].x = 2.0; obj.vertices[1].y = 3.0; obj.vertices[1].z = 4.0;
    obj.vertices[2].x = 3.0; obj.vertices[2].y = 4.0; obj.vertices[2].z = 5.0;
    obj.vertices[3].x = 4.0; obj.vertices[3].y = 5.0; obj.vertices[3].z = 6.0;
}

void teardown(void) {
    // Очистка ресурсов после тестов
    clean_obj(&obj);
}

START_TEST(test_move_x) {
    move_x(&obj, 1.5);

    // Проверяем, что все вершины сместились по оси X на 1.5
    ck_assert_float_eq_tol(obj.vertices[0].x, 2.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].x, 3.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].x, 4.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].x, 5.5, EPS);

    // Проверяем, что значения Y и Z остались без изменений
    ck_assert_float_eq_tol(obj.vertices[0].y, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 3.0, EPS);
}
END_TEST

START_TEST(test_rotate_y) {
    rotate_y(&obj, M_PI / 2);  // Поворот на 90 градусов

    // После поворота на 90 градусов по оси Y, координаты должны измениться согласно формулам
    ck_assert_float_eq_tol(obj.vertices[0].x, -3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].y, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 1.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[1].x, -4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].y, 3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].z, 2.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[2].x, -5.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].y, 4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].z, 3.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[3].x, -6.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].y, 5.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].z, 4.0, EPS);
}
END_TEST

START_TEST(test_rotate_x) {
    rotate_x(&obj, M_PI / 2);  // Поворот на 90 градусов

    // После поворота на 90 градусов по оси X, координаты должны измениться согласно формулам
    ck_assert_float_eq_tol(obj.vertices[0].x, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].y, -3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 2.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[1].x, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].y, -4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].z, 3.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[2].x, 3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].y, -5.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].z, 4.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[3].x, 4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].y, -6.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].z, 5.0, EPS);
}
END_TEST

START_TEST(test_rotate_z) {
    rotate_z(&obj, M_PI / 2);  // Поворот на 90 градусов

    // После поворота на 90 градусов по оси Z, координаты должны измениться согласно формулам
    ck_assert_float_eq_tol(obj.vertices[0].x, -2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].y, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 3.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[1].x, -3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].y, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].z, 4.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[2].x, -4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].y, 3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].z, 5.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[3].x, -5.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].y, 4.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].z, 6.0, EPS);
}
END_TEST

START_TEST(test_move_y) {
    move_y(&obj, -1.0);

    // Проверяем, что все вершины сместились по оси Y на -1.0
    ck_assert_float_eq_tol(obj.vertices[0].y, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].y, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].y, 3.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].y, 4.0, EPS);

    // Проверяем, что значения X и Z остались без изменений
    ck_assert_float_eq_tol(obj.vertices[0].x, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 3.0, EPS);
}
END_TEST

START_TEST(test_move_z) {
    move_z(&obj, 2.0);

    // Проверяем, что все вершины сместились по оси Z на 2.0
    ck_assert_float_eq_tol(obj.vertices[0].z, 5.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].z, 6.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].z, 7.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].z, 8.0, EPS);

    // Проверяем, что значения X и Y остались без изменений
    ck_assert_float_eq_tol(obj.vertices[0].x, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].y, 2.0, EPS);
}
END_TEST

START_TEST(test_scale) {
    scale(&obj, 0.5);

    // Проверяем, что все координаты вершин уменьшились в два раза
    ck_assert_float_eq_tol(obj.vertices[0].x, 0.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].y, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[0].z, 1.5, EPS);

    ck_assert_float_eq_tol(obj.vertices[1].x, 1.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].y, 1.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[1].z, 2.0, EPS);

    ck_assert_float_eq_tol(obj.vertices[2].x, 1.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].y, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[2].z, 2.5, EPS);

    ck_assert_float_eq_tol(obj.vertices[3].x, 2.0, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].y, 2.5, EPS);
    ck_assert_float_eq_tol(obj.vertices[3].z, 3.0, EPS);
}
END_TEST

Suite *obj_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Object Tests");

    // Core test case
    tc_core = tcase_create("Core");

    // Добавление тестовых функций
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_move_x);
    tcase_add_test(tc_core, test_rotate_y);
    tcase_add_test(tc_core, test_rotate_x);
    tcase_add_test(tc_core, test_rotate_z);
    tcase_add_test(tc_core, test_move_y);
    tcase_add_test(tc_core, test_move_z);
    tcase_add_test(tc_core, test_scale);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = obj_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}








