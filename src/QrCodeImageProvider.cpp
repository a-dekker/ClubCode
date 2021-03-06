/*
 * Copyright (C) 2019 Jolla Ltd.
 * Copyright (C) 2019 Slava Monich <slava@monich.com>
 *
 * You may use this file under the terms of BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "QrCodeImageProvider.h"

#include "HarbourBase32.h"
#include "HarbourDebug.h"

#include <QRgb>

QImage QrCodeImageProvider::requestImage(const QString& aId, QSize* aSize, const QSize&)
{
    const QByteArray bits(HarbourBase32::fromBase32(aId.toLocal8Bit()));
    QImage img;
    HDEBUG(aId << "=>" << bits.size() << "bytes");
    if (bits.size() > 0) {
        // Bits are packed, rows are rounded at byte boundary
        int rows, rowSize;
        for (rows = 2; ((rowSize = (rows + 7)/8) * rows) < bits.size(); rows++);
        if ((rows * rowSize) == bits.size()) {
            HDEBUG(rows << "x" << rows);
            img = QImage(rows, rows, QImage::Format_Mono);
            // Black on white
            QVector<QRgb> colors;
            colors.append(qRgb(0xff,0xff,0xff));
            colors.append(qRgb(0,0,0));
            img.setColorTable(colors);
            for (int y = 0; y < rows; y++) {
                memcpy(img.scanLine(y), bits.constData() + y * rowSize, rowSize);
            }
        }
    }

    if (!img.isNull() && aSize) {
        *aSize = img.size();
    }

    return img;
}
