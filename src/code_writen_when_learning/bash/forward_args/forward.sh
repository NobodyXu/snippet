#!/bin/bash
forward() {
    ls "$@"
}
forward "$@"
