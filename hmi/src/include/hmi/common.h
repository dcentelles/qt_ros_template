#ifndef HMI_COMMON_H
#define HMI_COMMON_H
namespace hmi {
class ButtonsStatus {
public:
  ButtonsStatus();
  bool up, down, left, right, tleft, tright, forward, reverse;
};
} // namespace hmi

#endif
