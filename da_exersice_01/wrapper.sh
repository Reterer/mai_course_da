#! /usr/bin/env bash

function log() {
    local type=$1
    local message=$2
    echo "[${type}] ${message}"
}

function log_error() {
    log "error" "$@"
}

function log_info() {
    log "info" "$@"
}

function main() {
    log_info "Stage #1 Compiling..."
    if ! make -C solution; then
        log_error "Failed to compile."
        return 1
    fi

    log_info "Stage #2 tests generating..."
    local test_dir="tests"
    if ! test -d "${test_dir}"; then
        mkdir "${test_dir}"
        ./generator.py "${test_dir}"
    else
        while true; do
        read -p "Do you want recreate tests y/n? " yn
        case $yn in
            [Yy]* )
                rm -r "${test_dir}" 
                mkdir "${test_dir}"
                ./generator.py "${test_dir}"
                break;;
            [Nn]* ) 
                break;;
            * ) 
                echo "Please answer yes or no.";;
        esac
    done
    fi

    log_info "Stage #3 Checking..."
    for test_file in $( ls ${test_dir}/*.t ) ; do
        local tmp_output=tmp
        if ! ./solution/solution < ${test_file} > ${tmp_output} ; then
            log_error "Failed to run test"
            rm "${tmp_output}"
            return 1
        fi
        local file_line_cnt=$(wc -l < ${test_file})
        local answer_file=${test_file%.*}.a
        if ! diff -u ${tmp_output} ${answer_file} ; then
            log_error "Failed to check test ${test_file}."
            rm "${tmp_output}"
            return 1
        fi
        log_info "${test_file}, lines=${file_line_cnt} OK"
        rm "${tmp_output}"
    done

    log_info "Stage #4 Benchmarking..."
    local benchmark_bin=./solution/benchmark
    for test_file in $( ls ${test_dir}/*.t ) ; do
        log_info "Running ${test_file}"
        if ! ${benchmark_bin} < ${test_file} ; then
            log_error "Failed to run ${benchmark_bin} for ${test_file}."
            return 1
        fi
        echo
    done
}

main "$@"