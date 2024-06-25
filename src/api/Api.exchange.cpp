#include <stdexcept>
#include <variant>
#include <vector>

#include "api/Api.hpp"
#include "api/types.hpp"

namespace kdeck
{
    ExchangeAnnouncementsResponse Api::GetExchangeAnnouncements()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        ApiResult<ExchangeAnnouncementsResponse> res = GetRequest<ExchangeAnnouncementsResponse>("/exchange/announcements");

        if (std::holds_alternative<ExchangeAnnouncementsResponse>(res))
        {
            announcements = std::get<ExchangeAnnouncementsResponse>(res);
        }
        else
        {
            throw std::runtime_error(std::get<ErrorResponse>(res).message);
        }

        return announcements;
    }

    ExchangeScheduleResponse Api::GetExchangeSchedule()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        ApiResult<ExchangeScheduleResponse> res = GetRequest<ExchangeScheduleResponse>("/exchange/schedule");

        if (std::holds_alternative<ExchangeScheduleResponse>(res))
        {
            schedule = std::get<ExchangeScheduleResponse>(res);
        }
        else
        {
            throw std::runtime_error(std::get<ErrorResponse>(res).message);
        }

        return schedule;
    }

    ExchangeStatusResponse Api::GetExchangeStatus()
    {
        // we don't need to be logged in!
        // if (!IsLoggedIn())
        // {
        //     throw std::logic_error("Not logged in.");
        // }

        ApiResult<ExchangeStatusResponse> res = GetRequest<ExchangeStatusResponse>("/exchange/status");

        if (std::holds_alternative<ExchangeStatusResponse>(res))
        {
            status = std::get<ExchangeStatusResponse>(res);
        }
        else
        {
            throw std::runtime_error(std::get<ErrorResponse>(res).message);
        }

        return status;
    }
}
