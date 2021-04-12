echo "Start OpenMP approach"

for ((i = 0; i<30; i++))
do
  echo "Test Perfeito $i"
  time mpirun -np 4 mpi_t ../../dados-SPD/11-20001/p10001.txt 10001
  echo "-------"
done
