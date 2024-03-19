#include <stdint.h>
#define OOF_IMPL
#include <oof.h>

// Explicit instantiations that are currently used
template void oof::write_sequence_into_string<std::string, oof::cursor_visibility_sequence>(std::string &, const oof::cursor_visibility_sequence &);
template void oof::write_sequence_into_string<std::string, oof::reset_sequence>(std::string &, const oof::reset_sequence &);
template void oof::write_sequence_into_string<std::string, oof::clear_screen_sequence>(std::string &, const oof::clear_screen_sequence &);
template void oof::write_sequence_into_string<std::string, oof::position_sequence>(std::string &, const oof::position_sequence &);
template void oof::write_sequence_into_string<std::string, oof::bold_sequence>(std::string &, const oof::bold_sequence &);
