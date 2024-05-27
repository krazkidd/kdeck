#include "api/Api.h"

bool Api::IsLoggedIn()
{
    return !member_id.empty();
}
