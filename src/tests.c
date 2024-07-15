#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "header.h"

#define LENGTH 256
#define EPSILON 1e-6

void* my_malloc() {
    return NULL;
}

static inline int assert_double_eq(double expected, double actual) {
    if (fabs(expected - actual) > EPSILON) {
        printf("expected: %f, actual: %f\n", expected, actual);
        return 0;
    } else {
        return 1;
    }
}

START_TEST(test_obj_create) {
  int res = 0;
    object_t *obj;
    res = create_obj(&obj);
    ck_assert_int_eq(res, OK);
    clean_obj(&obj);
}
END_TEST

START_TEST(test_pars_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *filename = "models/cube.obj";
  res = parse_obj_file(filename, obj);
  clean_obj(&obj);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_pars_2) {
  int res = 0;
  object_t *obj = NULL;
  char *filename = "";
  res = parse_obj_file(filename, obj);
  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(test_pars_3) {
  int res = 0;
  object_t *obj = NULL;
  char *filename = "no_file.obj";
  create_obj(&obj);
  res = parse_obj_file(filename, obj);
  ck_assert_int_eq(res, ERROR);;
  clean_obj(&obj);
}
END_TEST

START_TEST(test_clean_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  clean_obj(&obj);
  if (obj != NULL) {
    res = ERROR;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_clean_2) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  clean_obj(&obj);
  if (obj != NULL) {
    res = ERROR;
}
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(test_write_ind_vertices_1) {
  int res  = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *line = "f 1 2 3\n";
  res = write_ind_vertices(line, obj);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->num_faces, 1);
  ck_assert_int_eq(obj->faces[0].num_indices_in_face, 3);
  ck_assert_int_eq(obj->faces[0].vertex_indices[0], 1);
  ck_assert_int_eq(obj->faces[0].vertex_indices[1], 2);
  ck_assert_int_eq(obj->faces[0].vertex_indices[2], 3);
  clean_obj(&obj);
}
END_TEST

START_TEST(test_write_ind_vertices_2) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *line[] = {
        "f 1 2 3",
        "f 1 2 3\n"
  };
  for (size_t i = 0; i < sizeof(line) / sizeof(line[0]); i++) {
    res = write_ind_vertices(line[i], obj);
    ck_assert_int_eq(res, OK);
    ck_assert_int_eq(obj->faces[i].vertex_indices[0], 1);
    ck_assert_int_eq(obj->faces[i].vertex_indices[1], 2);
    ck_assert_int_eq(obj->faces[i].vertex_indices[2], 3);
  }
  ck_assert_int_eq(obj->num_faces, 2);
  clean_obj(&obj);
}
END_TEST

START_TEST(test_write_coord_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *line = "v 1.0 2.0 3.0\n";
  res = write_coord_vertex(line, obj);
  ck_assert_int_eq(res, OK);
  ck_assert(assert_double_eq(obj->points[0].x, 1.0));
  ck_assert(assert_double_eq(obj->points[0].y, 2.0));
  ck_assert(assert_double_eq(obj->points[0].z, 3.0));
  ck_assert_int_eq(obj->num_vertices, 1);
  clean_obj(&obj);
}
END_TEST

START_TEST(test_write_coord_2) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *line = "v -1.0 -2.0 -3.0\n";
  res = write_coord_vertex(line, obj);
  ck_assert_int_eq(res, OK);
  ck_assert(assert_double_eq(obj->points[0].x, -1.0));
  ck_assert(assert_double_eq(obj->points[0].y, -2.0));
  ck_assert(assert_double_eq(obj->points[0].z, -3.0));
  ck_assert_int_eq(obj->num_vertices, 1);
  clean_obj(&obj);
}

END_TEST

START_TEST(test_add_face_to_obj_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  unsigned indices[100] = {0};
  int num_indices = 0;
  char *line = "f 1 2 3\n";
  write_ind_vertices(line, obj);
  res = add_face_to_obj(obj, indices, num_indices);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->faces[0].num_indices_in_face, 3);
  ck_assert_int_eq(obj->faces[0].vertex_indices[0], 1);
  ck_assert_int_eq(obj->faces[0].vertex_indices[1], 2);
  ck_assert_int_eq(obj->faces[0].vertex_indices[2], 3);
  clean_obj(&obj);
}

END_TEST

START_TEST(test_add_vertex_to_obj_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double x = 0.0, y = 0.0, z = 0.0;
  double coord[3] = {x, y, z};
  char *line = "v 2.0 3.0 4.0\n";
  write_coord_vertex(line, obj);
  res = add_vertex_to_obj(obj, coord);
  ck_assert_int_eq(res, OK);
  ck_assert(assert_double_eq(obj->points[0].x, 2.0));
  ck_assert(assert_double_eq(obj->points[0].y, 3.0));
  ck_assert(assert_double_eq(obj->points[0].z, 4.0));
  clean_obj(&obj);
}
END_TEST

START_TEST(test_pars_obj_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  char *filename = "models/cube.obj";
  res = parse_obj_file(filename, obj);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->num_faces, 6);
  ck_assert_int_eq(obj->num_vertices, 8);
  ck_assert_int_eq(obj->line_num, 12);
  clean_obj(&obj);
}   

END_TEST

START_TEST(test_move_x_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double val = 1.0;
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  res = move_x(obj, val);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->num_vertices, 8);
  ck_assert(assert_double_eq(obj->points[0].x, 0.0));
  ck_assert(assert_double_eq(obj->points[1].x, 2.0));
  ck_assert(assert_double_eq(obj->points[2].x, 2.0));
  ck_assert(assert_double_eq(obj->points[3].x, 0.0));
  ck_assert(assert_double_eq(obj->points[4].x, 0.0));
  ck_assert(assert_double_eq(obj->points[5].x, 2.0));
  ck_assert(assert_double_eq(obj->points[6].x, 2.0));
  ck_assert(assert_double_eq(obj->points[7].x, 0.0));
  clean_obj(&obj);
}

END_TEST

START_TEST(test_move_y_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = 2.0;
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  res = move_y(obj, angle);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->num_vertices, 8);
  ck_assert(assert_double_eq(obj->points[0].y, 1.0));
  ck_assert(assert_double_eq(obj->points[1].y, 1.0));
  ck_assert(assert_double_eq(obj->points[2].y, 3.0));
  ck_assert(assert_double_eq(obj->points[3].y, 3.0));
  ck_assert(assert_double_eq(obj->points[4].y, 1.0));
  ck_assert(assert_double_eq(obj->points[5].y, 1.0));
  ck_assert(assert_double_eq(obj->points[6].y, 3.0));
  ck_assert(assert_double_eq(obj->points[7].y, 3.0));
  clean_obj(&obj);
}

END_TEST

START_TEST(test_move_z_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = 2.0;
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  res = move_z(obj, angle);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(obj->num_vertices, 8);
  ck_assert(assert_double_eq(obj->points[0].z, 1.0));
  ck_assert(assert_double_eq(obj->points[1].z, 1.0));
  ck_assert(assert_double_eq(obj->points[2].z, 1.0));
  ck_assert(assert_double_eq(obj->points[3].z, 1.0));
  ck_assert(assert_double_eq(obj->points[4].z, 3.0));
  ck_assert(assert_double_eq(obj->points[5].z, 3.0));
  ck_assert(assert_double_eq(obj->points[6].z, 3.0));
  ck_assert(assert_double_eq(obj->points[7].z, 3.0));
  clean_obj(&obj);
}

END_TEST

START_TEST(test_scale) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = 2.0;
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  vertex_t original_points[obj->num_vertices];
  for (int i = 0; i < obj->num_vertices; i++) {
      original_points[i] = obj->points[i];
  }
  res = scale(obj, angle);
  ck_assert_int_eq(res, OK);
  for (int i = 0; i < obj->num_vertices; i++) {
      ck_assert(assert_double_eq(obj->points[i].x, original_points[i].x * angle));
      ck_assert(assert_double_eq(obj->points[i].y, original_points[i].y * angle));
      ck_assert(assert_double_eq(obj->points[i].z, original_points[i].z * angle));
  }
  clean_obj(&obj);
}

END_TEST

START_TEST(test_rotate_x) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = M_PI / 2.0;
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  vertex_t original_points[obj->num_vertices];
  for (int i = 0; i < obj->num_vertices; i++) {
      original_points[i] = obj->points[i];
  }
  res = rotate_x(obj, angle);
  ck_assert_int_eq(res, OK);
  for (int i = 0; i < obj->num_vertices; i++) {
      ck_assert(assert_double_eq(obj->points[i].x, original_points[i].x));
      ck_assert(assert_double_eq(obj->points[i].y, original_points[i].y * cos_angle - original_points[i].z * sin_angle));
      ck_assert(assert_double_eq(obj->points[i].z, original_points[i].y * sin_angle + original_points[i].z * cos_angle));
  }
  clean_obj(&obj);
}

END_TEST

START_TEST(test_rotate_y) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = M_PI * 2.0;
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  vertex_t original_points[obj->num_vertices];
  for (int i = 0; i < obj->num_vertices; i++) {
    original_points[i] = obj->points[i];
  }
  res = rotate_y(obj, angle);
  ck_assert_int_eq(res, OK);
  for (int i = 0; i < obj->num_vertices; i++) {
    ck_assert(assert_double_eq(obj->points[i].x, original_points[i].x * cos_angle - original_points[i].z * sin_angle));
    ck_assert(assert_double_eq(obj->points[i].y, original_points[i].y));
    ck_assert(assert_double_eq(obj->points[i].z, original_points[i].x * sin_angle + original_points[i].z * cos_angle));
  }
  clean_obj(&obj);
}

END_TEST

START_TEST(test_rotate_z) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double angle = M_PI / 2.0;
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  vertex_t original_points[obj->num_vertices];
  for (int i = 0; i < obj->num_vertices; i++) {
    original_points[i] = obj->points[i];
  }
  res = rotate_z(obj, angle);
  ck_assert_int_eq(res, OK);
  for (int i = 0; i < obj->num_vertices; i++) {
    ck_assert(assert_double_eq(obj->points[i].x, original_points[i].x * cos_angle - original_points[i].y * sin_angle));
    ck_assert(assert_double_eq(obj->points[i].y, original_points[i].x * sin_angle + original_points[i].y * cos_angle));
    ck_assert(assert_double_eq(obj->points[i].z, original_points[i].z));
  }
  clean_obj(&obj);
}

END_TEST

START_TEST(test_min_max_1) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double min_x, max_x, min_y, max_y, min_z, max_z;
  char *filename = "models/cube.obj";
  parse_obj_file(filename, obj);
  res = find_min_max_coords(obj, &min_x, &max_x, &min_y, &max_y, &min_z, &max_z);
  ck_assert_int_eq(res, OK);
  ck_assert(assert_double_eq(min_x, -1.0));
  ck_assert(assert_double_eq(max_x, 1.0));
  ck_assert(assert_double_eq(min_y, -1.0));
  ck_assert(assert_double_eq(max_y, 1.0));
  ck_assert(assert_double_eq(min_z, -1.0));
  ck_assert(assert_double_eq(max_z, 1.0));
  clean_obj(&obj);
}

END_TEST

START_TEST(test_min_max_2) {
  int res = 0;
  object_t *obj = NULL;
  create_obj(&obj);
  double min_x_val, max_x_val, min_y_val, max_y_val, min_z_val, max_z_val;
  double *min_x = &min_x_val, *max_x = &max_x_val;
  double *min_y = &min_y_val, *max_y = &max_y_val;
  double *min_z = &min_z_val, *max_z = &max_z_val;
  char *filename = "models/skull.obj";
  parse_obj_file(filename, obj);
  res = find_min_max_coords(obj, min_x, max_x, min_y, max_y, min_z, max_z);
  ck_assert_int_eq(res, OK);
  ck_assert(assert_double_eq(min_x_val, -9.920400));
  ck_assert(assert_double_eq(max_x_val, 9.919900));
  ck_assert(assert_double_eq(min_y_val, -15.487700));
  ck_assert(assert_double_eq(max_y_val, 13.964300));
  ck_assert(assert_double_eq(min_z_val,  0.050200));
  ck_assert(assert_double_eq(max_z_val, 27.5759));
  clean_obj(&obj);
}

END_TEST

Suite *Viewer3D_suite_1(void) {
  Suite *s = suite_create("\x1b[33mTEST_CREATE\x1b[0m");
  TCase *tcase_create_obj = tcase_create("test_obj_create");
  suite_add_tcase(s, tcase_create_obj);
  tcase_add_test(tcase_create_obj, test_obj_create);
  return s;
}

Suite *Viewer3D_suite_2(void) {
  Suite *s = suite_create("\x1b[33mTEST_PARS\x1b[0m");
  TCase *tcase_pars = tcase_create("test_pars");
  suite_add_tcase(s, tcase_pars);
  tcase_add_test(tcase_pars, test_pars_1);
  tcase_add_test(tcase_pars, test_pars_2);
  tcase_add_test(tcase_pars, test_pars_3);
  return s;
}

Suite *Viewer3D_suite_3(void) {
  Suite *s = suite_create("\x1b[33mTEST_CLEAN\x1b[0m");
  TCase *tcase_clean = tcase_create("test_clean");
  suite_add_tcase(s, tcase_clean);
  tcase_add_test(tcase_clean, test_clean_1);
  tcase_add_test(tcase_clean, test_clean_2);
  return s;
}

Suite *Viewer3D_suite_4(void) {
  Suite *s = suite_create("\x1b[33mTEST_INDEXES\x1b[0m");
  TCase *tcase_write_ind_vert = tcase_create("test_write_ind_vertices");
  suite_add_tcase(s, tcase_write_ind_vert);
  tcase_add_test(tcase_write_ind_vert, test_write_ind_vertices_1);
  tcase_add_test(tcase_write_ind_vert, test_write_ind_vertices_2);
  return s;
}

Suite *Viewer3D_suite_5(void) {
  Suite *s = suite_create("\x1b[33mTEST_COORDINATES\x1b[0m");
  TCase *tcase_write_coord = tcase_create("test_write_coord");
  suite_add_tcase(s, tcase_write_coord);
  tcase_add_test(tcase_write_coord, test_write_coord_1);
  tcase_add_test(tcase_write_coord, test_write_coord_2);
  return s;
}


Suite *Viewer3D_suite_6(void) {
  Suite *s = suite_create("\x1b[33mTEST_ADD_FACES\x1b[0m");
  TCase *tcase_add_face = tcase_create("test_add_face_to_obj");
  suite_add_tcase(s, tcase_add_face);
  tcase_add_test(tcase_add_face, test_add_face_to_obj_1);
  return s;
}

Suite *Viewer3D_suite_7(void) {
  Suite *s = suite_create("\x1b[33mTEST_ADD_VERTICES\x1b[0m");
  TCase *tcase_add_vert = tcase_create("test_add_vertex_to_obj");
  suite_add_tcase(s, tcase_add_vert);
  tcase_add_test(tcase_add_vert, test_add_vertex_to_obj_1);
  return s;
}

Suite *Viewer3D_suite_8(void) {
  Suite *s = suite_create("\x1b[33mTEST_PARSE_OBJ\x1b[0m");
  TCase *tcase_pars_obj = tcase_create("test_pars_obj");
  suite_add_tcase(s, tcase_pars_obj);
  tcase_add_test(tcase_pars_obj, test_pars_obj_1);
  return s;
}

Suite *Viewer3D_suite_9(void) {
  Suite *s = suite_create("\x1b[33mTEST_MOVE\x1b[0m");
  TCase *tcase_move = tcase_create("test_moeve");
  suite_add_tcase(s,tcase_move);
  tcase_add_test(tcase_move, test_move_x_1);
  tcase_add_test(tcase_move, test_move_y_1);
  tcase_add_test(tcase_move, test_move_z_1);
  return s;
}


Suite *Viewer3D_suite_10(void) {
  Suite *s = suite_create("\x1b[33mTEST_SCALE\x1b[0m");
  TCase *tcase_scale = tcase_create("test_scale");
  suite_add_tcase(s, tcase_scale);
  tcase_add_test(tcase_scale, test_scale);
  return s;
}

Suite *Viewer3D_suite_11(void) {
  Suite *s = suite_create("\x1b[33mTEST_ROTATE\x1b[0m");
  TCase *tcase_rotate = tcase_create("test_rotate");
  suite_add_tcase(s, tcase_rotate);
  tcase_add_test(tcase_rotate, test_rotate_x);
  tcase_add_test(tcase_rotate, test_rotate_y);
  tcase_add_test(tcase_rotate, test_rotate_z);
  return s;
}


Suite *Viewer3D_suite_12(void) {
  Suite *s = suite_create("\x1b[33mTEST_MIN_MAX\x1b[0m");
  TCase *tcase_min_max = tcase_create("test_min_max");
  suite_add_tcase(s, tcase_min_max);
  tcase_add_test(tcase_min_max, test_min_max_1);
  tcase_add_test(tcase_min_max, test_min_max_2);
  return s;
}

int main(void) {
  Suite *list_cases[] = {
    Viewer3D_suite_1(),
    Viewer3D_suite_2(),
    Viewer3D_suite_3(),
    Viewer3D_suite_4(),
    Viewer3D_suite_5(),
    Viewer3D_suite_6(),
    Viewer3D_suite_7(),
    Viewer3D_suite_8(),
    Viewer3D_suite_9(),
    Viewer3D_suite_10(),
    Viewer3D_suite_11(),
    Viewer3D_suite_12(), NULL
  };

  int fail_count = 0;
  printf("\x1b[36mS21_3DVIEWER TESTS...\x1b[0m\n");
  for (int i = 0; list_cases[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(list_cases[i]);
    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);
    fail_count += srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }
  printf("\x1b[32mTOTAL NUMBER OF FAILURES: %d\x1b[0m\n", fail_count);
  return fail_count;
}



      
  
