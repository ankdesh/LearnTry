# Compile
g++ qp3_solver.cpp main.cpp -o gp3placer
g++ demo.cpp solver.cpp -o solver
g++ combine_outx_outy.cpp -o combiner

# Check if the argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 /path/to/input file"
    exit 1
fi

# Get the full file path passed as an argument
full_path="$1"

# Extract the filename without the path using basename
filename=$(basename "$full_path")

# Remove the extension from the filename using sed
base_name=$(echo "$filename" | sed 's/\.[^.]*$//')

# Output the base name (filename without path and extension)
echo "Base Name: $base_name"

# Run
echo "Running Placer ..."
./gp3placer ${full_path} ${base_name} 

echo "Solving Equations..."
./solver ${base_name}.outA ${base_name}.outBx ${base_name}.outx
./solver ${base_name}.outA ${base_name}.outBy ${base_name}.outy 

echo "Combining Results..."
./combiner ${base_name}

# Move to results folder
mkdir -p results/
mv ${base_name} results/
