#include "WritableResultModel.hpp"

WritableResultModel::~WritableResultModel()
{
}

std::ofstream &operator<<(std::ofstream &file, const WritableResultModel &result)
{
  if (file.is_open() == false)
    {
      std::cout << "[BACKUP_LOGGER] Log file not open, result packet not written" << std::endl;
      return file;
    }
  if (result.getTheoreticalMaxScore() >= 0)
    {
      file << "{" << std::endl
	   << "  \"theoreticalMaxScore\": " << result.getTheoreticalMaxScore() << "," << std::endl
	   << "  \"results\": [" << std::endl;
      return file;
    }
  else if (result.getTheoreticalMaxScore() != -2)
    {
      if (result.getIteration() != 0)
	file << "," << std::endl;
      file << "    {" << std::endl
	   << "      \"iteration\": " << result.getIteration() << "," << std::endl
	   << "      \"maxScore\": " << result.getMaxScore() << "," << std::endl
	   << "      \"averageScore\": " << result.getAverageScore() << "," << std::endl
	   << "      \"worstScore\": " << result.getWorstScore() << std::endl;
    }
  if (result.getTheoreticalMaxScore() == -2)
    {
      file << std::endl
	   << "  ]"  << std::endl
	   << "}" << std::endl;
    }
  else
    file << "    }";
  return file;
}
