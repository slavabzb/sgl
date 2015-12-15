/* Copyright (c) 2015
 * 
 * Bezborodov, V.A. vyacheslav.bezborodov@gmail.com
 * Golodov, V.A. avaksa@gmail.com
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * @defgroup algo Algorithms
 * Algorithms.
 * 
 * @todo Kruskal's algorithm.
 * @todo Borůvka's algorithm.
 * @todo Fleury's algorithm.
 * @todo Kuhn–Munkres algorithm.
 * @todo Edmonds–Karp algorithm.
 * 
 * @defgroup core Core
 * Main parts.
 * 
 * @defgroup io I/O
 * Input/output.
 * 
 * @defgroup view Views
 * Representations.
 * 
 * @todo Iterators.
 */

#pragma once /** @file sgl.h Single header for @ref sgl library. */

#include <sgl/algo/prim.h>

#include <sgl/core/edge.h>
#include <sgl/core/graph.h>
#include <sgl/core/node.h>

#include <sgl/io/reader.h>
#include <sgl/io/writer.h>
#include <sgl/io/simple_reader.h>
#include <sgl/io/simple_writer.h>

#include <sgl/view/view.h>
#include <sgl/view/type.h>
#include <sgl/view/adjacency_matrix.h>
#include <sgl/view/adjacency_list.h>
#include <sgl/view/edge_list.h>
