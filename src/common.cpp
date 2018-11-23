#include <hmi/common.h>

namespace hmi {

ButtonsStatus::ButtonsStatus()
    : up(false), down(false), left(false), right(false), tleft(false),
      tright(false), forward(false), reverse(false) {}

} // namespace hmi
