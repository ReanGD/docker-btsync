#pragma once
#include <cstdint>

struct Settings {
  static const uint16_t m_botSizePixel = 10;
  static const uint16_t m_worldMaxXPixel = 1000;
  static const uint16_t m_worldMaxYPixel = 800;
  static const uint16_t m_worldMaxX = m_worldMaxXPixel / m_botSizePixel;
  static const uint16_t m_worldMaxY = m_worldMaxXPixel / m_botSizePixel;
  static const uint32_t m_worldMaxCoord = static_cast<uint32_t>(m_worldMaxX) * static_cast<uint32_t>(m_worldMaxY);
};
