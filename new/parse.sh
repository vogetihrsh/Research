shopt -s extglob

# PARAMETERS  
window_length=100;
no_of_procs=32;

input_file="";	# required
mappability_file=""; # required
window_file=""; # required
config_file="" # optional 

output="";      # required
SOURCEDIR=$(dirname $(readlink -f $0));

cflag=0
# SCANNING FOR PARAMETERS
while getopts 'w:p:i:o:m:z:c:' flag; do
	case "${flag}" in 
	w) window_length="${OPTARG}"  ;;
	p) no_of_procs="${OPTARG}" ;;
	i) input_file="${OPTARG}" ;;
	o) output="${OPTARG}"  ;;
	m) mappability_file="${OPTARG}" ;;
	z) window_file="${OPTARG}" ;;
	c) config_file="${OPTARG}" cflag=1;;
	\?) echo "Invalid option: -$OPTARG" >&2
	esac 
done

# IF YOU USE -C CHECK IF CONFIG FILE EXISTS
if [[ ! -f $config_file && $cflag -eq 1 ]]; then 
	echo "Config File $config_file not found"
	exit 

elif [ $cflag -eq 1 ]; then 
#PARSE INPUT FILE AND GET PARAMETERS
	tr -d '\r' < $config_file > $output"config.temp"
	while IFS='= ' read lhs rhs
	do
		if [[ ! $lhs =~ ^\ *'#' && -n $lhs ]]; then
			rhs="${rhs%%\#*}"    # Del in line right comments
			rhs="${rhs%%*( )}"   # Del trailing spaces
			rhs="${rhs%\"*}"     # Del opening string quotes 
			rhs="${rhs#\"*}"     # Del closing string quotes 
			declare $lhs="$rhs"
		fi
	done < $output"config.temp"
	rm -rf $output"config.temp"
fi	

# MINIMUM REQUIRED PARAMETERS
if [[ -z "$input_file" || -z "$window_file" || -z "$mappability_file" || -z "$output" ]]; then
	echo "Missing one of the required parameters: window_file (-z) mappability_file (-m) input_file (-i) output (-o) " >&2
	exit 
fi

# FILE DOESNT EXIST ERROR
if [[ ! -f $window_file || ! -f $input_file || ! -f $mappability_file ]]; then 
	echo "One of the input files not found" >&2
	exit
fi
echo $window_length
