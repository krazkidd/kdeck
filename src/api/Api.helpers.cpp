#include "api/Api.h"

bool Api::IsLoggedIn()
{
    return !login.member_id.empty();
}
