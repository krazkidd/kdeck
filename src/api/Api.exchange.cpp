#include <stdexcept>
#include <variant>
#include <vector>

#include "oatpp/core/base/Environment.hpp"

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{
    std::shared_ptr<ExchangeAnnouncementsResponse> Api::GetExchangeAnnouncements()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        OATPP_LOGD("Api", "GetExchangeAnnouncements");

        ApiResult<ExchangeAnnouncementsResponse> res = HandleResponse<ExchangeAnnouncementsResponse>(_api->GetExchangeAnnouncements(basePath));

        if (std::holds_alternative<std::shared_ptr<ExchangeAnnouncementsResponse>>(res))
        {
            announcements = std::get<std::shared_ptr<ExchangeAnnouncementsResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return announcements;
    }

    std::shared_ptr<ExchangeScheduleResponse> Api::GetExchangeSchedule()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        OATPP_LOGD("Api", "GetExchangeSchedule");

        ApiResult<ExchangeScheduleResponse> res = HandleResponse<ExchangeScheduleResponse>(_api->GetExchangeSchedule(basePath));

        if (std::holds_alternative<std::shared_ptr<ExchangeScheduleResponse>>(res))
        {
            schedule = std::get<std::shared_ptr<ExchangeScheduleResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return schedule;
    }

    std::shared_ptr<ExchangeStatusResponse> Api::GetExchangeStatus()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        OATPP_LOGD("Api", "GetExchangeStatus");

        ApiResult<ExchangeStatusResponse> res = HandleResponse<ExchangeStatusResponse>(_api->GetExchangeStatus(basePath));

        if (std::holds_alternative<std::shared_ptr<ExchangeStatusResponse>>(res))
        {
            status = std::get<std::shared_ptr<ExchangeStatusResponse>>(res);
        }
        else
        {
            throw std::runtime_error(std::get<std::shared_ptr<ErrorResponse>>(res)->error->message->c_str());
        }

        return status;
    }
}
