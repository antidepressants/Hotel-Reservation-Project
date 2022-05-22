#pragma once
#include "classes.h"
#include <hpdf_types.h>

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
void exportTotal(user* u);